#define LOG_TAG "NST_TEST"
#define LOG_NDEBUG 0
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <utils/Log.h>
#include <string.h>
#include <pthread.h>

#include "IHelloService.h"

using namespace android;
using namespace android::os;

sp<IHelloService> gHelloService;
const char* kHelloServiceName = "hello.service";

const sp<IHelloService> getHelloService()
{
    sp<IHelloService> nsts;
    int retryCnt = 3;
    {
        if (gHelloService == 0) {
            sp<IServiceManager> sm = defaultServiceManager();
            sp<IBinder> binder;
            do {
                binder = sm->getService(String16(kHelloServiceName));
                if (binder != 0) {
                    break;
                }
                usleep(50000);
            } while (retryCnt--);
            if (binder == 0) {
                return NULL;
            }
            gHelloService = interface_cast<IHelloService>(binder);
        }
        nsts = gHelloService;
    }
    return nsts;
}

static void* thread_fun(void*)
{
    const sp<IHelloService> service = getHelloService();
    if (service == 0) {
        return NULL;
    }

    //test data
    service->helloWorld();
    printf("helloService called!\n");
    return NULL;
}


int main(int argc, char **argv)
{
    printf("nsts test start!!\n");

    // retrieve service
    const sp<IHelloService>& service = getHelloService();
    if (service == 0) {
        return NO_INIT;
    }
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_t threadId;
    int ret = pthread_create(&threadId, &attr, &thread_fun, (void*)0 );
    if (ret!=0) {
        printf("Create pthread error!\n");
        return -1;
    }

    pthread_attr_destroy(&attr);
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();

    return 0;
}

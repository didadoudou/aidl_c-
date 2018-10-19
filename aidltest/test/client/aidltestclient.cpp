#define LOG_TAG "NST_TEST"
#define LOG_NDEBUG 0
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <utils/Log.h>
#include <string.h>
#include <pthread.h>
#include <binder/PersistableBundle.h>

#include <android/os/IHelloService.h>
#include <sec/BnSecResultReceiver.h>

using namespace android;
using namespace android::os;

sp<IHelloService> gHelloService;
const char* kHelloServiceName = "hello.service";


static int registerReceiver();


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

static int sayHello()
{
    const sp<IHelloService> service = getHelloService();
    if (service == 0) {
        return NULL;
    }

    //test data
    service->helloWorld();
    printf("helloService called!\n");
    return NO_ERROR;
}

static void* thread_fun(void*)
{
//    const sp<IHelloService> service = getHelloService();
//    if (service == 0) {
//        return NULL;
//    }

    //test data
//    service->helloWorld();
//    printf("helloService called!\n");
    sayHello();
    return NULL;
}


static void* reg_thread_func(void*)
{
    printf("reg_thread_func called!");
    registerReceiver();
    sayHello();
    return NULL;
}


class SecResultReceiver : public sec::BnSecResultReceiver,
    public IBinder::DeathRecipient
{
public:
    SecResultReceiver() {
        ALOGD("Result Receiver constructor");
    }

    void binderDied(const wp<IBinder>& who __unused) {
        ALOGD("hello server died!");
    }

    android::binder::Status send(int32_t resultCode) {

        printf("SecResultReceiver->send called!, resultCode: %d", resultCode);
	return android::binder::Status::ok();
    }
};


static int registerReceiver()
{
    const sp<IHelloService> service = getHelloService();
    if (service == 0) {
        return NULL;
    }
    service->registerReceiver(new SecResultReceiver());
    return NO_ERROR;
}



int main(int argc, char **argv)
{
    printf("nsts test start!!\n");

    // retrieve service
//    const sp<IHelloService>& service = getHelloService();
//    if (service == 0) {
//        return NO_INIT;
//    }
//    registerReceiver();
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_t threadId;
    int ret = pthread_create(&threadId, &attr, &reg_thread_func, (void*)0 );
    if (ret!=0) {
        printf("Create pthread error!\n");
        return -1;
    }

    pthread_attr_destroy(&attr);
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();

    return 0;
}

#include "HelloService.h" 
#include <cutils/log.h> 
#include <binder/IServiceManager.h> 
#include <binder/IPCThreadState.h> 
#define PROGRESS_LOCK_SHARED 1
#define VHALAIDLLOCK "vhalaidllock"


namespace android 
{
namespace os
{
	HelloService::HelloService() 
	{
		VectorRwLock = new Mutex(PROGRESS_LOCK_SHARED,VHALAIDLLOCK);

                mNotifyClients = new DefaultKeyedVector<pid_t, sp<NotifyClient>>();

       	} 
	

	HelloService::~HelloService() 
	{ } 
	

	int HelloService::instantiate() 
	{ 
		int ret = defaultServiceManager()->addService( String16("hello.service"), new HelloService());
		return ret; 
	}
       
	android::binder::Status HelloService::helloWorld() 
	{ 
		printf("HelloService::HelloWorld\n"); 
		notifyClients(true);
		return android::binder::Status::ok();
	} 

	void HelloService::removeNotifyClient(pid_t  pid)
        {
                VectorRwLock->lock();
                mNotifyClients->removeItem(pid);
                VectorRwLock->unlock();
        }


	android::binder::Status HelloService::registerReceiver(const sp<sec::ISecResultReceiver>& receiver)
        {
                int rc ,rc1;
                ALOGD("%s ", __FUNCTION__);
                pid_t pid = IPCThreadState::self()->getCallingPid();

                VectorRwLock->lock();
                rc1 = mNotifyClients->indexOfKey(pid);
                rc = (rc1 < 0 );

                if(rc) {

                            sp<NotifyClient> notifyClient = new NotifyClient(this, receiver, pid);
                            ALOGD("registerClient pid=%d", pid);
			    ALOGD("HelloService->registerReceiver called!");
                            mNotifyClients->add(pid, notifyClient);
                            sp<IBinder> binder = IInterface::asBinder(receiver);
                            binder->linkToDeath(notifyClient);



                }
	       	else {
                            ALOGD("client already registerd! pid=%d", pid);
			    ALOGD("HelloService->registerReceiver already called!");
                }
                VectorRwLock->unlock();
                return android::binder::Status::ok();
        }

       
	void HelloService::notifyClients(bool integrity)
	{
	        ALOGD("HelloService->notifyClients called!");
                VectorRwLock->lock();
                
		for (size_t i=0; i<mNotifyClients->size(); i++)
		{
			sp<sec::ISecResultReceiver> client = mNotifyClients->valueAt(i)->getReceiverClient();
			client->send(integrity);
		}


		VectorRwLock->unlock();
	}

	HelloService::NotifyClient::NotifyClient( const sp<HelloService>& testService, const sp<sec::ISecResultReceiver>& client, pid_t pid)
        :mService(testService),  mPid(pid), mReceiverClient(client)
        {
               ALOGD("new HelloService.NotifyClient %s", __FUNCTION__);
        }

        HelloService::NotifyClient::~NotifyClient()
        {
        }

        void HelloService::NotifyClient::binderDied(const wp<IBinder>& who __unused)
        {
               ALOGD("Enter %s ,pid =%d", __FUNCTION__ ,mPid);

               sp<NotifyClient> keep(this);
               mService->removeNotifyClient(mPid);
        }

}
}

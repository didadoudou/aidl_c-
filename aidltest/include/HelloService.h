#include <android/os/BnHelloService.h>
#include <cutils/log.h> 
#include <utils/RefBase.h> 
#include <binder/IServiceManager.h> 
#include <binder/IPCThreadState.h> 
#include <sec/ISecResultReceiver.h>
#include <mutex>
#include <utils/KeyedVector.h>

namespace android
{ 
namespace os
{
	class HelloService : public BnHelloService 
	{ 
		public: 
			static int instantiate(); 
		private: 
			HelloService(); 
			virtual ~HelloService(); 
			virtual android::binder::Status helloWorld();
			virtual android::binder::Status registerReceiver(const sp<sec::ISecResultReceiver>& receiver);
			void removeNotifyClient(pid_t pid);
			void notifyClients(bool integrity);


	        class NotifyClient : public IBinder::DeathRecipient
                {
                    public:
                           NotifyClient(const sp<HelloService>& testService, const sp<sec::ISecResultReceiver>& client, pid_t pid);
                           virtual ~NotifyClient();

                           const sp<sec::ISecResultReceiver> getReceiverClient() {
                                 return mReceiverClient;
                           }

                           virtual void binderDied(const wp<IBinder>& who);

                    private:
                            const sp<HelloService> mService;
                            const pid_t mPid;
                            const sp<sec::ISecResultReceiver> mReceiverClient;
               };

	Mutex *VectorRwLock;
        DefaultKeyedVector<pid_t, sp<NotifyClient> >* mNotifyClients;
	}; 
};
};

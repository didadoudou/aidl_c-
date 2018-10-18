#include <android/os/BnHelloService.h>
#include <cutils/log.h> 
#include <utils/RefBase.h> 
#include <binder/IServiceManager.h> 
#include <binder/IPCThreadState.h> 


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
	}; 
};
};

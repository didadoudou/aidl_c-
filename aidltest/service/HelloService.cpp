#include "HelloService.h" 
#include <cutils/log.h> 
#include <binder/IServiceManager.h> 
#include <binder/IPCThreadState.h> 


namespace android 
{
namespace os
{
	HelloService::HelloService() 
	{ } 
	

	HelloService::~HelloService() 
	{ } 
	

	int HelloService::instantiate() 
	{ 
		int ret = defaultServiceManager()->addService( String16("hello.service"), new HelloService());
		return ret; }
       
	android::binder::Status HelloService::helloWorld() 
	{ 
		printf("HelloService::HelloWorld\n"); 
		return android::binder::Status::ok();
	} 
}
}

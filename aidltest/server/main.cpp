#include <binder/IPCThreadState.h> 
#include <binder/ProcessState.h> 
#include <binder/IServiceManager.h> 
#include <stdio.h> 
#include <HelloService.h> 

using namespace android;
using namespace android::os;

int main(void) 
{ 
	printf("Hello server - main() begin\n"); 
	sp<ProcessState> proc(ProcessState::self()); 
	int ret = HelloService::instantiate();
       	printf("Hello server -Hello Service::Instance return %d\n", ret); 
	ProcessState::self()->startThreadPool(); 
	IPCThreadState::self()->joinThreadPool(); 
	return 0; 
}

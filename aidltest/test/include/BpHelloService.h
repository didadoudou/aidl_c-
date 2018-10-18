#ifndef AIDL_GENERATED_ANDROID_OS_BP_HELLO_SERVICE_H_
#define AIDL_GENERATED_ANDROID_OS_BP_HELLO_SERVICE_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include "IHelloService.h"

namespace android {

namespace os {

class BpHelloService : public ::android::BpInterface<IHelloService> {
public:
explicit BpHelloService(const ::android::sp<::android::IBinder>& _aidl_impl);
virtual ~BpHelloService() = default;
::android::binder::Status helloWorld() override;
};  // class BpHelloService

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_BP_HELLO_SERVICE_H_

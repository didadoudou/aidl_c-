#ifndef AIDL_GENERATED_ANDROID_OS_I_HELLO_SERVICE_H_
#define AIDL_GENERATED_ANDROID_OS_I_HELLO_SERVICE_H_

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <utils/StrongPointer.h>

namespace android {

namespace os {

class IHelloService : public ::android::IInterface {
public:
DECLARE_META_INTERFACE(HelloService)
virtual ::android::binder::Status helloWorld() = 0;
enum Call {
  HELLOWORLD = ::android::IBinder::FIRST_CALL_TRANSACTION + 0,
};
};  // class IHelloService

}  // namespace os

}  // namespace android

#endif  // AIDL_GENERATED_ANDROID_OS_I_HELLO_SERVICE_H_

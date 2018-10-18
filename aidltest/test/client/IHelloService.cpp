#include "IHelloService.h"
#include "BpHelloService.h"

namespace android {

namespace os {

IMPLEMENT_META_INTERFACE(HelloService, "android.os.IHelloService")

}  // namespace os

}  // namespace android


#include "BpHelloService.h"
#include <binder/Parcel.h>

namespace android {

namespace os {

BpHelloService::BpHelloService(const ::android::sp<::android::IBinder>& _aidl_impl)
    : BpInterface<IHelloService>(_aidl_impl){
}

::android::binder::Status BpHelloService::helloWorld() {
::android::Parcel _aidl_data;
::android::Parcel _aidl_reply;
::android::status_t _aidl_ret_status = ::android::OK;
::android::binder::Status _aidl_status;
_aidl_ret_status = _aidl_data.writeInterfaceToken(getInterfaceDescriptor());
if (((_aidl_ret_status) != (::android::OK))) {
goto _aidl_error;
}
_aidl_ret_status = remote()->transact(IHelloService::HELLOWORLD, _aidl_data, &_aidl_reply);
if (((_aidl_ret_status) != (::android::OK))) {
goto _aidl_error;
}
_aidl_ret_status = _aidl_status.readFromParcel(_aidl_reply);
if (((_aidl_ret_status) != (::android::OK))) {
goto _aidl_error;
}
if (!_aidl_status.isOk()) {
return _aidl_status;
}
_aidl_error:
_aidl_status.setFromStatusT(_aidl_ret_status);
return _aidl_status;
}

}  // namespace os

}  // namespace android

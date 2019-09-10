#include <assert.h>
#include <string>
#include "mdspi.h"

napi_ref WrapperMd::constructor;

WrapperMd::WrapperMd(const string &ip, int port)
    : env_(nullptr), wrapper_(nullptr) {
      m_ptrMdApi = CThostFtdcMdApi::CreateFtdcMdApi();
      m_ptrMdSpi = new MdSpi();
      mdApi->RegisterSpi(m_ptrMdSpi);
      m_ptrMdApi->Init();
    }

WrapperMd::~WrapperMd() {
    m_ptrMdApi->Release();
    delete m_ptrMdSpi;
    delete m_ptrMdApi;
    napi_delete_reference(env_, wrapper_);
}

void WrapperMd::Destructor(napi_env env, void* nativeObject, void* /*finalize_hint*/) {
  reinterpret_cast<WrapperMd*>(nativeObject)->~WrapperMd();
}

#define DECLARE_NAPI_METHOD(name, func)                          \
  { name, 0, func, 0, 0, 0, napi_default, 0 }

napi_value WrapperMd::Init(napi_env env, napi_value exports) {
  napi_status status;
  napi_property_descriptor properties[] = {
      DECLARE_NAPI_METHOD("login", login),
      DECLARE_NAPI_METHOD("logout", logout),
  };

  napi_value cons;
  status =
      napi_define_class(env, "WrapperMd", NAPI_AUTO_LENGTH, New, nullptr, 2, properties, &cons);
  assert(status == napi_ok);

  status = napi_create_reference(env, cons, 1, &constructor);
  assert(status == napi_ok);

  status = napi_set_named_property(env, exports, "WrapperMd", cons);
  assert(status == napi_ok);
  return exports;
}

napi_value WrapperMd::New(napi_env env, napi_callback_info info) {
  napi_status status;

  napi_value target;
  status = napi_get_new_target(env, info, &target);
  assert(status == napi_ok);
  bool is_constructor = target != nullptr;

  if (is_constructor) {
    // Invoked as constructor: `new WrapperMd()`
    size_t argc = 0;
    napi_value args[0];
    napi_value jsthis;
    status = napi_get_cb_info(env, info, &argc, args, &jsthis, nullptr);
    assert(status == napi_ok);

    WrapperMd* obj = new WrapperMd();

    obj->env_ = env;
    status = napi_wrap(env,
                       jsthis,
                       reinterpret_cast<void*>(obj),
                       WrapperMd::Destructor,
                       nullptr,  // finalize_hint
                       &obj->wrapper_);
    assert(status == napi_ok);

    return jsthis;
  }
}

napi_value WrapperMd::RegisterFront(napi_env env, napi_callback_info info) {
  napi_status status;

  size_t argc = 1;
  napi_value args[1];
  napi_value jsthis;
  status = napi_get_cb_info(env, info, &argc, args, &jsthis, nullptr);
  assert(status == napi_ok);

  napi_valuetype frontAddressType;
  status = napi_typeof(env, args[0], &frontAddressType);
  assert(status == napi_ok);


  char frontAddressBuf[20];
  size_t frontAddressSize;
  if (frontAddressType != napi_undefined) {
    status = napi_get_value_string_utf8(env, args[0], frontAddressBuf, 20, &frontAddressSize);
    assert(status == napi_ok);
  }
  std::string frontAddress(frontAddressBuf);


  WrapperMd* obj;
  status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
  assert(status == napi_ok);

  obj->m_ptrMdApi->RegisterFront(frontAddress.c_str());

  return;
}
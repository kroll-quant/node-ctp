#include <assert.h>
#include <string>
#include "mdspi.h"
#include "wrapper_md.h"
#include <vector>

using namespace std;

napi_ref WrapperMd::constructor;

WrapperMd::WrapperMd()
    : env_(nullptr), wrapper_(nullptr), _reqId(0) {
      m_ptrMdApi = CThostFtdcMdApi::CreateFtdcMdApi();
      m_ptrMdSpi = new MdSpi();
      m_ptrMdApi->RegisterSpi(m_ptrMdSpi);
      m_ptrMdApi->Init();
    }

WrapperMd::~WrapperMd() {
    m_ptrMdApi->Release();
    delete this->m_ptrMdSpi;
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
      DECLARE_NAPI_METHOD("RegisterFront", RegisterFront),
      DECLARE_NAPI_METHOD("ReqUserLogin", ReqUserLogin),
	  DECLARE_NAPI_METHOD("ReqUserLogout", ReqUserLogout),
	  DECLARE_NAPI_METHOD("GetTradingDay", GetTradingDay),
	  DECLARE_NAPI_METHOD("SubscribeMarketData", SubscribeMarketData),
	  DECLARE_NAPI_METHOD("UnSubscribeMarketData", UnSubscribeMarketData)
  };

  napi_value cons;
  status =
      napi_define_class(env, "WrapperMd", NAPI_AUTO_LENGTH, New, nullptr, 6, properties, &cons);
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
    napi_value jsthis;
    status = napi_get_cb_info(env, info, &argc, nullptr, &jsthis, nullptr);
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
  }else{
	  // Invoked as plain function `WrapperMd(...)`, turn into construct call.
    napi_value cons;
    status = napi_get_reference_value(env, constructor, &cons);
    assert(status == napi_ok);

	size_t argc = 0;
    napi_value instance;
    status = napi_new_instance(env, cons, argc, nullptr, &instance);
    assert(status == napi_ok);

    return instance;
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

  obj->m_ptrMdApi->RegisterFront((char*)frontAddress.c_str());

  return NULL;
}

napi_value WrapperMd::ReqUserLogin(napi_env env, napi_callback_info info) {
  napi_status status;

  size_t argc = 3;
  napi_value args[3];
  napi_value jsthis;
  status = napi_get_cb_info(env, info, &argc, args, &jsthis, nullptr);
  assert(status == napi_ok);

  //获取参数: brokerId
  napi_valuetype brokerIdType;
  status = napi_typeof(env, args[0], &brokerIdType);
  assert(status == napi_ok);

  char brokerIdBuf[20];
  size_t brokerIdSize;
  if (brokerIdType != napi_undefined) {
    status = napi_get_value_string_utf8(env, args[0], brokerIdBuf, 20, &brokerIdSize);
    assert(status == napi_ok);
  }
  std::string brokerId(brokerIdBuf);

  //获取参数: userId
  napi_valuetype userIdType;
  status = napi_typeof(env, args[1], &userIdType);
  assert(status == napi_ok);

  char userIdBuf[20];
  size_t userIdSize;
  if (userIdType != napi_undefined) {
    status = napi_get_value_string_utf8(env, args[1], userIdBuf, 20, &userIdSize);
    assert(status == napi_ok);
  }
  std::string userId(userIdBuf);


  //获取参数: password
  napi_valuetype passwordType;
  status = napi_typeof(env, args[0], &passwordType);
  assert(status == napi_ok);

  char passwordBuf[20];
  size_t passwordSize;
  if (passwordType != napi_undefined) {
    status = napi_get_value_string_utf8(env, args[2], passwordBuf, 20, &passwordSize);
    assert(status == napi_ok);
  }
  std::string password(passwordBuf);


  //调用ctp相应接口
  WrapperMd* obj;
  status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
  assert(status == napi_ok);

  CThostFtdcReqUserLoginField reqField;
  memset(&reqField, 0, sizeof(reqField));
  strcpy(reqField.BrokerID, brokerId.c_str());
  strcpy(reqField.UserID, userId.c_str());
  strcpy(reqField.Password, password.c_str());

  int retValue = obj->m_ptrMdApi->ReqUserLogin(&reqField, ++obj->_reqId);

  napi_value rst;
  status = napi_create_int32(env, retValue, &rst);
  assert(status == napi_ok);

  return rst;
}

napi_value WrapperMd::ReqUserLogout(napi_env env, napi_callback_info info) {
  napi_status status;

  size_t argc = 2;
  napi_value args[2];
  napi_value jsthis;
  status = napi_get_cb_info(env, info, &argc, args, &jsthis, nullptr);
  assert(status == napi_ok);

  //获取参数: brokerId
  napi_valuetype brokerIdType;
  status = napi_typeof(env, args[0], &brokerIdType);
  assert(status == napi_ok);

  char brokerIdBuf[20];
  size_t brokerIdSize;
  if (brokerIdType != napi_undefined) {
    status = napi_get_value_string_utf8(env, args[0], brokerIdBuf, 20, &brokerIdSize);
    assert(status == napi_ok);
  }
  std::string brokerId(brokerIdBuf);

  //获取参数: userId
  napi_valuetype userIdType;
  status = napi_typeof(env, args[1], &userIdType);
  assert(status == napi_ok);

  char userIdBuf[20];
  size_t userIdSize;
  if (userIdType != napi_undefined) {
    status = napi_get_value_string_utf8(env, args[1], userIdBuf, 20, &userIdSize);
    assert(status == napi_ok);
  }
  std::string userId(userIdBuf);

  //调用ctp相应接口
  WrapperMd* obj;
  status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
  assert(status == napi_ok);

  CThostFtdcUserLogoutField reqField;
  memset(&reqField, 0, sizeof(reqField));
  strcpy(reqField.BrokerID, brokerId.c_str());
  strcpy(reqField.UserID, userId.c_str());

  int retValue = obj->m_ptrMdApi->ReqUserLogout(&reqField, ++obj->_reqId);

  napi_value rst;
  status = napi_create_int32(env, retValue, &rst);
  assert(status == napi_ok);

  return rst;
}

napi_value WrapperMd::GetTradingDay(napi_env env, napi_callback_info info) {
  napi_status status;

  size_t argc = 0;
  napi_value jsthis;
  status = napi_get_cb_info(env, info, &argc, nullptr, &jsthis, nullptr);
  assert(status == napi_ok);


  WrapperMd* obj;
  status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
  assert(status == napi_ok);

  const char* tradingDay = obj->m_ptrMdApi->GetTradingDay();

  napi_value rst;
  status = napi_create_string_utf8(env, tradingDay, NAPI_AUTO_LENGTH, &rst);
  assert(status == napi_ok);

  return rst;
}

napi_value WrapperMd::SubscribeMarketData(napi_env env, napi_callback_info info) {
  napi_status status;

  size_t argc = 1;
  napi_value args[1];
  napi_value jsthis;
  status = napi_get_cb_info(env, info, &argc, args, &jsthis, nullptr);
  assert(status == napi_ok);

  
  std:vector<std::string> vec;
  uint32_t i, length;
  status = napi_get_array_length(env, args[0], &length);
  for (i = 0; i < length; i++)
  {
    napi_value e;
    status = napi_get_element(env, args[0], i, &e);
	assert(status == napi_ok);

	char buf[20];
	size_t bufSize;
	status = napi_get_value_string_utf8(env, e, buf, 20, &bufSize);
	assert(status == napi_ok);

	vec.push_back(std::string(buf));
  }
 
  int nCount = vec.size();
  char** ppInstrumentID = new char*[nCount];
  for(int i=0; i < nCount; i++){
	ppInstrumentID[i] = (char*)vec[i].c_str();
  }

  WrapperMd* obj;
  status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
  assert(status == napi_ok);

  int retValue = obj->m_ptrMdApi->SubscribeMarketData(ppInstrumentID, nCount);

  napi_value rst;
  status = napi_create_int32(env, retValue, &rst);
  assert(status == napi_ok);

  //析构ppInstrumentID
  for(int i=0; i < nCount; i++){
	delete ppInstrumentID[i];
  }

  return rst;
}

napi_value WrapperMd::UnSubscribeMarketData(napi_env env, napi_callback_info info) {
  napi_status status;

  size_t argc = 1;
  napi_value args[1];
  napi_value jsthis;
  status = napi_get_cb_info(env, info, &argc, args, &jsthis, nullptr);
  assert(status == napi_ok);

  
  std:vector<std::string> vec;
  uint32_t i, length;
  status = napi_get_array_length(env, args[0], &length);
  for (i = 0; i < length; i++)
  {
    napi_value e;
    status = napi_get_element(env, args[0], i, &e);
	assert(status == napi_ok);

	char buf[20];
	size_t bufSize;
	status = napi_get_value_string_utf8(env, e, buf, 20, &bufSize);
	assert(status == napi_ok);

	vec.push_back(std::string(buf));
  }
 
  int nCount = vec.size();
  char** ppInstrumentID = new char*[nCount];
  for(int i=0; i < nCount; i++){
	ppInstrumentID[i] = (char*)vec[i].c_str();
  }

  WrapperMd* obj;
  status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
  assert(status == napi_ok);

  int retValue = obj->m_ptrMdApi->UnSubscribeMarketData(ppInstrumentID, nCount);

  napi_value rst;
  status = napi_create_int32(env, retValue, &rst);
  assert(status == napi_ok);

  //析构ppInstrumentID
  for(int i=0; i < nCount; i++){
	delete ppInstrumentID[i];
  }

  return rst;
}
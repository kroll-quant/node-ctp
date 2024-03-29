#ifndef WRAPPER_MD_H
#define WRAPPER_MD_H

#include <assert.h>
#include <node_api.h>
#include "ThostFtdcMdApi.h"
#include "mdspi.h"

class WrapperMd {
 public:
  static napi_value Init(napi_env env, napi_value exports);
  static void Destructor(napi_env env, void* nativeObject, void* finalize_hint);

  int _reqId;

 private:
  explicit WrapperMd(napi_env env, napi_value OnFrontConnected);
  ~WrapperMd();
  static napi_value New(napi_env env, napi_callback_info info);
  static napi_ref constructor;

  napi_env env_;
  napi_ref wrapper_;

  CThostFtdcMdApi* m_ptrMdApi;
  MdSpi* m_ptrMdSpi;

  /*
    下面是封装的mdApi接口
  */
  static napi_value RegisterFront(napi_env env, napi_callback_info info);
  static napi_value ReqUserLogin(napi_env env, napi_callback_info info);
  static napi_value ReqUserLogout(napi_env env, napi_callback_info info);
  static napi_value GetTradingDay(napi_env env, napi_callback_info info);
  static napi_value SubscribeMarketData(napi_env env, napi_callback_info info);
  static napi_value UnSubscribeMarketData(napi_env env, napi_callback_info info);

  /*
    回调函数
  */
  napi_threadsafe_function _tsOnFrontConnected;


};

#endif

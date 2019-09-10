#include <assert.h>
#include <node_api.h>
#include "wrapper_md.h"

napi_value Init(napi_env env, napi_value exports) {
    WrapperMd::Init(env, exports);
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)

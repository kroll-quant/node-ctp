#include "wrapper_md.h"

napi_value Init(napi_env env, napi_value exports) {
	return WrapperMd::Init(env, exports);
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)

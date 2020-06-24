#include <napi.h>
#include "Renderer.h"





Napi::Object Init(Napi::Env env, Napi::Object exports) {

  //Initialize library
  Renderer::Init(env, exports);
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)
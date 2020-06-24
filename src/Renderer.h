#ifndef RENDERER_H
#define RENDERER_H

#include <napi.h>
#include <string>
#include <locale>
#include <codecvt>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Color.h"

enum Color_t {
  R=0, G=1, B=2, A=3
};


std::string errorString(FT_Error code);

class Renderer : public Napi::ObjectWrap<Renderer> {
  public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    Renderer(const Napi::CallbackInfo &info);
    ~Renderer();

    Napi::Value Open(const Napi::CallbackInfo& info);
    Napi::Value Clear(const Napi::CallbackInfo& info);
    Napi::Value Draw(const Napi::CallbackInfo& info);

    Napi::Value GetSize(const Napi::CallbackInfo& info);
    void SetSize (const Napi::CallbackInfo& info, const Napi::Value&);

    Napi::Value GetColor (const Napi::CallbackInfo& info);
    void SetColor (const Napi::CallbackInfo& info, const Napi::Value &value);

    Napi::Value GetBuffer(const Napi::CallbackInfo& info);
  
  private:
    static Napi::FunctionReference constructor;
    //freetype structures
    FT_Library library;
    FT_Face face;

    //Buffer space
    std::vector<uint8_t> buf;
    FT_Int width;
    FT_Int height;
    std::vector<uint8_t>::size_type getIndex(FT_Int x, FT_Int y, Color_t c);

    //font configuration
    signed long fontSize;
    Color color;

};



#endif
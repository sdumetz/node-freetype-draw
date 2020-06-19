#include <napi.h>
#include <ft2build.h>
#include FT_FREETYPE_H

enum Color {
  R=0, G=1, B=2, A=3
};


std::string errorString(FT_Error code){
  const char* s = FT_Error_String(code);
  if(s == nullptr){
    return "(Unknown error)";
  }else{
    return s;
  }
}

class Renderer : public Napi::ObjectWrap<Renderer> {
  public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    Renderer(const Napi::CallbackInfo &info);
    ~Renderer();

    Napi::Value Open(const Napi::CallbackInfo& info);
    Napi::Value Clear(const Napi::CallbackInfo& info);
    Napi::Value Draw(const Napi::CallbackInfo& info);
    Napi::Value GetBuffer(const Napi::CallbackInfo& info);
  private:
    static Napi::FunctionReference constructor;
    FT_Library library;
    FT_Face face;
    std::vector<uint8_t> buf;
    FT_Int width;
    FT_Int height;

    std::vector<uint8_t>::size_type getIndex(FT_Int x, FT_Int y, Color c);
};


Napi::Object Renderer::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  // This method is used to hook the accessor and method callbacks
  Napi::Function func = DefineClass(env, "Renderer", {
    InstanceMethod("open", &Renderer::Open),
    InstanceMethod("clear", &Renderer::Clear),
    InstanceMethod("draw", &Renderer::Draw),
    InstanceAccessor<&Renderer::GetBuffer>("buffer")
  });

  Napi::FunctionReference* constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent(func);
  env.SetInstanceData(constructor);
  exports.Set("Renderer", func);
  return exports;
}

Napi::Value Renderer::Open(const Napi::CallbackInfo& info){
  Napi::Env env = info.Env();
  if(! info[0].ToObject().Get("font").IsString()){
    throw Napi::Error::New(env, "Font path should be a string");
    return env.Undefined();
  }
  std::string fontpath = info[0].ToObject().Get("font").ToString().Utf8Value();

  FT_Error error = FT_New_Face( this->library,
                     fontpath.c_str(),
                     0,
                     &this->face );
  if ( error == FT_Err_Unknown_File_Format ) {
    throw Napi::Error::New(env, fontpath+" is not a valid font file");
  } else if ( error != FT_Err_Ok) {
    throw Napi::Error::New(env, fontpath+" failed to open with error "+errorString(error));
  }
  error = FT_Set_Char_Size(
          this->face,    /* handle to face object           */
          0,       /* char_width in 1/64th of points  */
          16<<6,   /* char_height in 1/64th of points */
          300,     /* horizontal device resolution    */
          300 );   /* vertical device resolution      */
  if ( error != FT_Err_Ok) {
    throw Napi::Error::New(env, "Failed to set font size "+errorString(error));
  }
  return env.Undefined();
}

std::vector<uint8_t>::size_type  Renderer::getIndex(FT_Int x, FT_Int y, Color c){
  return (y*this->width + x) * 4 + (std::vector<uint8_t>::size_type) c;
}
Napi::Value Renderer::Clear(const Napi::CallbackInfo& info){
  Napi::Env env = info.Env();
  std::fill(buf.begin(), buf.end(), 0);
  return env.Undefined();
}

Napi::Value Renderer::Draw(const Napi::CallbackInfo& info){
  Napi::Env env = info.Env();
  FT_Error error;
  FT_Int i, j, p, q;
  FT_Vector     pen;
  FT_GlyphSlot  slot = face->glyph;  /* a small shortcut */

  std::string text = info[0].ToString().Utf8Value();

  Napi::Object args = (2 <= info.Length())? info[1].ToObject() : Napi::Object::New(env);
  pen.x = ((args.Has("x"))? args.Get("x").ToNumber().Int32Value() : 0);
  pen.y = ((args.Has("y"))? args.Get("y").ToNumber().Int32Value() : slot->bitmap_top);

  error = FT_Set_Char_Size(
        this->face,    /* handle to face object           */
        0,       /* char_width in 1/64th of points  */
        (args.Has("size")? args.Get("size").ToNumber().Int64Value() : 16 ) <<6,   /* char_height in 1/64th of points */
        72,     /* horizontal device resolution    */
        72 );   /* vertical device resolution      */
  if ( error != FT_Err_Ok) {
    throw Napi::Error::New(env, "Failed to set font size "+errorString(error));
  }


  for ( long unsigned int n = 0; n < text.length(); n++ )
  {
    /* load glyph image into the slot (erase previous one) */
    error = FT_Load_Char( face, text[n], FT_LOAD_RENDER );
    if ( error ){
      continue;  /* ignore errors */
    }

    FT_Int x = pen.x + slot->bitmap_left;
    FT_Int y = pen.y - slot->bitmap_top;
    FT_Int x_max = x + slot->bitmap.width;
    FT_Int y_max =  y + slot->bitmap.rows;

    for ( i = x, p = 0; i < x_max; i++, p++ ) {
      for ( j = y, q = 0; j < y_max; j++, q++ ) {
        if ( i < 0 || j < 0 || i >= this->width || j >= this->height ) {
          continue;
        }
        this->buf[getIndex(i, j, Color::B)] |= slot->bitmap.buffer[q * slot->bitmap.width + p];
        this->buf[getIndex(i, j, Color::G)] |= slot->bitmap.buffer[q * slot->bitmap.width + p];
        this->buf[getIndex(i, j, Color::R)] |= slot->bitmap.buffer[q * slot->bitmap.width + p];
        this->buf[getIndex(i, j, Color::A)] |= (slot->bitmap.buffer[q * slot->bitmap.width + p] == 0x00)? 0x00 : 0xFF;
      }
    }

    //move pen
    pen.x += slot->advance.x >> 6;
    //pen.y += slot->advance.y;
  }
  return env.Undefined();
}


Napi::Value Renderer::GetBuffer(const Napi::CallbackInfo &info){
  Napi::Env env = info.Env();
  return Napi::Buffer<uint8_t>::New(env, this->buf.data(), this->buf.size());
}

Renderer::Renderer(const Napi::CallbackInfo &info) : Napi::ObjectWrap<Renderer>(info), buf() {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);


  FT_Error error = FT_Init_FreeType( &this->library );
  if ( error ) {
    throw Napi::Error::New(env, "Failed to init freetype with error : "+errorString(error));
    return;
  }
  Napi::Object arg = (0 == info.Length())? Napi::Object::New(env) : info[0].ToObject();

  if(arg.Has("font")){
    this->Open(info);
  }else{
    this->face = nullptr;
  }
  this->width = arg.Has("width")? arg.Get("width").ToNumber().Uint32Value() : 400;
  this->height = arg.Has("height")? arg.Get("height").ToNumber().Uint32Value() : 300;
  this->buf.resize(this->width*this->height*4, 0x00);
}


Renderer::~Renderer(){
  if(this->face != nullptr) FT_Done_Face(this->face);
  FT_Done_FreeType(this->library);
}


Napi::Object Init(Napi::Env env, Napi::Object exports) {

  //Initialize library
  Renderer::Init(env, exports);
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)
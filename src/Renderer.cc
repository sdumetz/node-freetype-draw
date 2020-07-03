#include "Renderer.h"




std::string errorString(FT_Error code){
  const char* s = FT_Error_String(code);
  if(s == nullptr){
    return "(Unknown error)";
  }else{
    return s;
  }
}

Napi::Object Renderer::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  // This method is used to hook the accessor and method callbacks
  Napi::Function func = DefineClass(env, "Renderer", {
    InstanceMethod("open", &Renderer::Open),
    InstanceMethod("clear", &Renderer::Clear),
    InstanceMethod("draw", &Renderer::Draw),
    InstanceAccessor<&Renderer::GetSize, &Renderer::SetSize>("size"),
    InstanceAccessor<&Renderer::GetColor, &Renderer::SetColor>("color"),
    InstanceAccessor<&Renderer::GetBuffer>("buffer"),
  });

  Napi::FunctionReference* constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent(func);

  #if NAPI_VERSION > 5
  env.SetInstanceData(constructor);
  #endif

  exports.Set("Renderer", func);
  return exports;
}


Renderer::Renderer(const Napi::CallbackInfo &info) : 
  Napi::ObjectWrap<Renderer>(info), 
  buf(),
  fontSize(12),
  color()
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);


  FT_Error error = FT_Init_FreeType( &this->library );
  if ( error ) {
    throw Napi::Error::New(env, "Failed to init freetype with error : "+errorString(error));
    return;
  }
  Napi::Object arg = (0 == info.Length())? Napi::Object::New(env) : info[0].ToObject();
    this->width = arg.Has("width")? arg.Get("width").ToNumber().Uint32Value() : 400;
  this->height = arg.Has("height")? arg.Get("height").ToNumber().Uint32Value() : 300;
  this->buf.resize(this->width*this->height*4, 0x00);


  if(arg.Has("font")){
    this->Open(info);
  }else{
    this->face = nullptr;
  }
}


Renderer::~Renderer(){
  if(this->face != nullptr) FT_Done_Face(this->face);
  FT_Done_FreeType(this->library);
}


Napi::Value Renderer::Open(const Napi::CallbackInfo& info){
  Napi::Env env = info.Env();
  Napi::Object arg =  info[0].ToObject();
  if(! arg.Get("font").IsString()){
    throw Napi::Error::New(env, "Font path should be a string");
    return env.Undefined();
  }
  std::string fontpath = arg.Get("font").ToString().Utf8Value();

  FT_Error error = FT_New_Face( this->library,
                     fontpath.c_str(),
                     0,
                     &this->face );
  if ( error == FT_Err_Unknown_File_Format ) {
    throw Napi::Error::New(env, fontpath+" is not a valid font file");
  } else if ( error != FT_Err_Ok) {
    throw Napi::Error::New(env, fontpath+" failed to open with error "+errorString(error));
  }

  error = FT_Select_Charmap(face, FT_ENCODING_UNICODE);
  if(error != FT_Err_Ok){
    throw Napi::Error::New(env, "Selected font does not have an unicode charmap "+errorString(error));
  }
  if(arg.Has("size")){
    this->SetSize(info, arg.Get("size"));
  }else{
    this->SetSize(info, Napi::Number::New(env, this->fontSize));
  }

  return env.Undefined();
}

void Renderer::SetSize (const Napi::CallbackInfo& info, const Napi::Value &value){
  Napi::Env env = info.Env();
  if(!value.IsNumber()){
    throw Napi::Error::New(env, "size argument must be a number");
  }
  this->fontSize = value.As<Napi::Number>().Int32Value();

  FT_Error error = FT_Set_Char_Size(
          this->face,    /* handle to face object           */
          0,       /* char_width in 1/64th of points  */
          this->fontSize <<6,   /* char_height in 1/64th of points */
          72,     /* horizontal device resolution    */
          72 );   /* vertical device resolution      */
  if ( error != FT_Err_Ok) {
    throw Napi::Error::New(env, "Failed to set font size "+errorString(error));
  }
}

Napi::Value Renderer::GetSize (const Napi::CallbackInfo& info){
  Napi::Env env = info.Env();
  return Napi::Number::New(env, this->fontSize);
}


void Renderer::SetColor (const Napi::CallbackInfo& info, const Napi::Value &value){
  Napi::Env env = info.Env();
  const std::string hexColor = value.ToString().Utf8Value();
  try{
    this->color = Color(hexColor);
  }catch(const std::invalid_argument& e){ //Normally, just "const std::invalid_argument&" exceptions from stoi
    throw Napi::Error::New(env, "Invalid argument : could not parse "+hexColor+ std::string(e.what()));
  }
}

Napi::Value Renderer::GetColor (const Napi::CallbackInfo& info){
  Napi::Env env = info.Env();
  return Napi::String::New(env, this->color.toString());
}

std::vector<uint8_t>::size_type  Renderer::getIndex(FT_Int x, FT_Int y, Color_t c){
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
  std::string utf8Text = info[0].ToString().Utf8Value();
  
  std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> cvt;
  std::u32string text = cvt.from_bytes(utf8Text);


  Napi::Object args = (2 <= info.Length())? info[1].ToObject() : Napi::Object::New(env);
  pen.x = ((args.Has("x"))? args.Get("x").ToNumber().Int32Value() : 0);
  pen.y = ((args.Has("y"))? args.Get("y").ToNumber().Int32Value() : slot->bitmap_top);


  for ( long unsigned int n = 0; n < text.size(); n++ )
  {
    /* load glyph image into the slot (erase previous one) */
    error = FT_Load_Char( face, text[n], FT_LOAD_DEFAULT );
    if ( error ){
      continue;  /* ignore errors */
    }
    if(slot->format != FT_GLYPH_FORMAT_BITMAP){
      error = FT_Render_Glyph( slot, 
        FT_RENDER_MODE_NORMAL );
      if ( error ){
        continue;  /* ignore errors */
      }
    }

    //
    FT_Int x = pen.x + slot->bitmap_left;
    FT_Int y = pen.y - slot->bitmap_top;
    FT_Int x_max = x + slot->bitmap.width;
    FT_Int y_max =  y + slot->bitmap.rows;

    for ( i = x, p = 0; i < x_max; i++, p++ ) {
      for ( j = y, q = 0; j < y_max; j++, q++ ) {
        if ( i < 0 || j < 0 || i >= this->width || j >= this->height ) {
          continue;
        }
        uint8_t a = slot->bitmap.buffer[q * slot->bitmap.width + p];
        this->buf[getIndex(i, j, Color_t::B)] |= (a == 0)? 0 : color.b;
        this->buf[getIndex(i, j, Color_t::G)] |= (a == 0)? 0 : color.g;
        this->buf[getIndex(i, j, Color_t::R)] |= (a == 0)? 0 : color.r;
        this->buf[getIndex(i, j, Color_t::A)] |= a * color.a/255;
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

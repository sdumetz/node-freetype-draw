#include "PixFmt.h"



PixFmt::PixFmt(): PixFmt("RGBA") {};


PixFmt::PixFmt(std::string fmt): str_fmt(fmt) {}


std::string PixFmt::toString(){
  return str_fmt;
}

size_t PixFmt::GetR(){
  return str_fmt.find("R");
}
size_t PixFmt::GetG(){
  return str_fmt.find("G");
}
size_t PixFmt::GetB(){
  return str_fmt.find("B");
}
size_t PixFmt::GetA(){
  return str_fmt.find("A");
}

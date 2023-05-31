#include "PixFmt.h"



PixFmt::PixFmt(): PixFmt("RGBA") {};

PixFmt::PixFmt(std::string fmt): str_fmt(fmt) {
  this->R  = str_fmt.find("R");
  this->G = str_fmt.find("G");
  this->B = str_fmt.find("B");
  this->A = str_fmt.find("A");
}


std::string PixFmt::toString(){
  return str_fmt;
}

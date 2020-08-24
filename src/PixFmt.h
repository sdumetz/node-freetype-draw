#ifndef PIXFMT_H
#define PIXFMT_H


#include <string>
#include <iostream>
#include <sstream>

class PixFmt {
  public:
    PixFmt();
    PixFmt(std::string);
    
    std::string toString();
    operator std::string() {
      return toString();
    }
    size_t GetR();
    size_t GetG();
    size_t GetB();
    size_t GetA();
  private:
    std::string str_fmt; 
};

#endif
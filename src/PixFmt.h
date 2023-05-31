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
    size_t R;
    size_t G;
    size_t B;
    size_t A;
  private:
    std::string str_fmt; 
};

#endif
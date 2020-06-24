#ifndef COLOR_H
#define COLOR_H

#include <string>
#include <iostream>
#include <sstream>


class Color {
  public:
    Color();
    Color(const std::string& hexColor);
    Color(uint8_t monochrome);
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
    std::string toString();
    operator std::string() {
      return toString();
    }
};

#endif
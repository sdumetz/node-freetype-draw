#include "Color.h"

Color::Color(): Color(0, 0, 0, 255) {};
Color::Color(uint8_t m): Color(m, m, m, 255) {};
Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {};

Color::Color(const std::string& hexColor): r(), g(), b(), a(255) {
  std::string c(hexColor);
  switch(hexColor.size()){
    case 9:
      c = hexColor.substr(1);
      [[fallthrough]];
    case 8:
        a = std::stoi(c.substr(6, 2),nullptr, 16);
        [[fallthrough]];
    case 7:
      c = hexColor.substr(1);
      [[fallthrough]];
    case 6:
        r = std::stoi(c.substr(0, 2), nullptr, 16);
        g = std::stoi(c.substr(2, 2), nullptr, 16);
        b = std::stoi(c.substr(4, 2), nullptr, 16);
    break;
    case 4:
      c = hexColor.substr(1);
      [[fallthrough]];
    case 3:
        r = std::stoi(c.substr(0, 1), nullptr, 16)*17;
        g = std::stoi(c.substr(1, 1), nullptr, 16)*17;
        b = std::stoi(c.substr(2, 1), nullptr, 16)*17;
    break;
    case 2:
      r = g = b = std::stoi(c.substr(0,2), nullptr, 16);
      break;
    default:
      throw std::invalid_argument( "bad string length" );
  };
};

std::string Color::toString(){
  std::stringstream sstream;
  sstream << std::uppercase << std::hex << "#" 
  << r/16 << r % 16
  << g/16 << g % 16
  << b/16 << b % 16
  << a/16 << a % 16;
  return sstream.str();
}
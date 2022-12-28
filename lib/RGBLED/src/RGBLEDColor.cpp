#include "RGBLEDColor.h"

RGBLED::Color::Color() : blue(1.0), green(1.0), red(1.0) {}

RGBLED::Color::Color(const double red, const double green, const double blue) : blue(blue), green(green), red(red) {}

RGBLED::Color::Color(const RGBLED::Color &copy) : RGBLED::Color::Color(copy.red, copy.green, copy.blue) {}

RGBLED::Color::~Color() {}

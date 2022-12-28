#ifndef RGB_LED_COLOR_H
#define RGB_LED_COLOR_H

namespace RGBLED
{
    class Color
    {
    public:
        double red;
        double green;
        double blue;

        Color();
        Color(const double red, const double green, const double blue);
        Color(const RGBLED::Color &copy);
        ~Color();
    };
};

#endif

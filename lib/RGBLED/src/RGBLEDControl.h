#ifndef RGB_LED_CONTROL_H
#define RGB_LED_CONTROL_H

#include "RGBLEDColor.h"

namespace RGBLED
{
    class Control
    {
    public:
        static RGBLED::Control *getSingleton();

        bool isOn() const;
        RGBLED::Color getColor() const;
        void setColor(const RGBLED::Color color);
        void toggle(bool on);
        void operator=(const RGBLED::Control &copy) = delete;

    private:
        RGBLED::Color color;
        static RGBLED::Control *singleton;

        Control();
        Control(const RGBLED::Control &copy) = delete;
        ~Control();
    };
};

#endif

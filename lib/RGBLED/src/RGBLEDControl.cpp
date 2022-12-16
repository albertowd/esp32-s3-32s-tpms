#include "RGBLEDControl.h"

#include <Arduino.h>

#include "RGBLEDColors.h"
#include "RGBLEDPIN.h"

RGBLED::Control *RGBLED::Control::singleton(nullptr);

RGBLED::Control::Control()
{
    pinMode(RGBLED::PIN::BLUE, OUTPUT);
    pinMode(RGBLED::PIN::GREEN, OUTPUT);
    pinMode(RGBLED::PIN::RED, OUTPUT);
    this->toggle(false);
}

bool RGBLED::Control::isOn() const
{
    return 0 != this->color.blue && 0 != this->color.green && 0 != this->color.red;
}

RGBLED::Control *RGBLED::Control::getSingleton()
{
    if (nullptr == RGBLED::Control::singleton)
    {
        RGBLED::Control::singleton = new RGBLED::Control();
    }
    return RGBLED::Control::singleton;
}

RGBLED::Color RGBLED::Control::getColor() const
{
    return this->color;
}

void RGBLED::Control::setColor(const Color color)
{
    if (0 <= color.blue && 255.0 >= color.blue &&
        0 <= color.green && 255.0 >= color.green &&
        0 <= color.red && 255.0 >= color.red)
    {
        this->color = color;
        analogWrite(RGBLED::PIN::BLUE, this->color.blue);
        analogWrite(RGBLED::PIN::GREEN, this->color.green);
        analogWrite(RGBLED::PIN::RED, this->color.red);
    }
}

void RGBLED::Control::toggle(bool on)
{
    if (on)
    {
        this->setColor(RGBLED::Colors::WHITE);
    }
    else
    {
        this->setColor(RGBLED::Colors::BLACK);
    }
}

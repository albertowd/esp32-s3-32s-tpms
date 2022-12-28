#ifdef ENABLE_TPMS_DISPLAY

#ifndef TPMS_DISPLAY_H
#define TPMS_DISPLAY_H

#include <TFT_eSPI.h>

namespace TPMSDisplay
{
    class Base
    {
    protected:
        static TFT_eSPI tft;

    public:
        static void begin();
        static void changeRotation();
        static void renderBlack();
        static void renderBoot();
    };
}

#endif

#endif
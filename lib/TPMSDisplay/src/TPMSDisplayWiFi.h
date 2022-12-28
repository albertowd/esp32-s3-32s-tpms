#ifdef ENABLE_TPMS_DISPLAY

#ifndef TPMS_DISPLAY_WIFI_H
#define TPMS_DISPLAY_WIFI_H

#include "TPMSDisplay.h"

namespace TPMSDisplay
{
    class WiFi : protected TPMSDisplay::Base
    {
    public:
        static void render(const char *ssid);
    };
}

#endif

#endif

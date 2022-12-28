#ifdef ENABLE_TPMS_DISPLAY

#include "TPMSDisplayWiFi.h"

void TPMSDisplay::WiFi::render(const char *wifiAddress)
{
    tft.fillScreen(TFT_CYAN);
    tft.setTextSize(1);
    tft.setTextColor(TFT_BLACK, TFT_CYAN);
    tft.drawString("Connecting to", 10, 23, 4);
    tft.drawString(wifiAddress, 10, 90, 4);
}

#endif

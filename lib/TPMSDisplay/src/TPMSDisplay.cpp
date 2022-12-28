#ifdef ENABLE_TPMS_DISPLAY

#include "TPMSDisplay.h"

TFT_eSPI TPMSDisplay::Base::tft;

void TPMSDisplay::Base::begin()
{
    tft.begin();
    tft.setRotation(3);
}

void TPMSDisplay::Base::changeRotation()
{
    tft.setRotation(3 == tft.getRotation() ? 1 : 3);
}

void TPMSDisplay::Base::renderBlack()
{
    tft.fillScreen(TFT_BLACK);
}

void TPMSDisplay::Base::renderBoot()
{
    tft.fillScreen(TFT_WHITE);
}

#endif

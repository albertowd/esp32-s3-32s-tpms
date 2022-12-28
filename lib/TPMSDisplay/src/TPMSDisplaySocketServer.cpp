#ifdef ENABLE_TPMS_DISPLAY

#include "TPMSDisplaySocketServer.h"

void TPMSDisplay::SocketServer::render(const char *socketAddress)
{
    tft.fillScreen(TFT_GREEN);
    tft.setTextSize(1);
    tft.setTextColor(TFT_BLACK, TFT_CYAN);
    tft.drawString("Listening on", 10, 23, 4);
    tft.drawString(socketAddress, 10, 90, 4);
}

#endif

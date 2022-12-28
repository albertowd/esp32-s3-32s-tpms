#ifdef ENABLE_TPMS_DISPLAY

#ifndef TPMS_DISPLAY_SOCKER_SERVER_H
#define TPMS_DISPLAY_SOCKER_SERVER_H

#include "TPMSDisplay.h"

namespace TPMSDisplay
{
    class SocketServer : protected TPMSDisplay::Base
    {
    public:
        static void render(const char *socketAddress);
    };
}

#endif

#endif

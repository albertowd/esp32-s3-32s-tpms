#ifdef ENABLE_TPMS_DISPLAY

#ifndef TPMS_DISPLAY_TYRE_H
#define TPMS_DISPLAY_TYRE_H

#include "TPMSDisplay.h"

namespace TPMSDisplay
{
    class Tyre : protected TPMSDisplay::Base
    {
    private:
        static double lastFLP;
        static double lastFLT;
        static double lastFRP;
        static double lastFRT;
        static double lastRLP;
        static double lastRLT;
        static double lastRRP;
        static double lastRRT;

    public:
        static bool areDiff(const double value1, const double value2);
        static unsigned int pressureColor(const double value);
        static unsigned int temperatureColor(const double value);
        static void renderFL(const double pressure, const double temperature);
        static void renderFR(const double pressure, const double temperature);
        static void renderRL(const double pressure, const double temperature);
        static void renderRR(const double pressure, const double temperature);
    };
}

#endif

#endif

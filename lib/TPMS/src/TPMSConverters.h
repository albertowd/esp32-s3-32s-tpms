#include "string"

#ifndef TPMS_CONVERTERS_H
#define TPMS_CONVERTERS_H

namespace TPMS
{
    class Converters
    {
    public:
        static float temperatureCToF(const float temperatureC);
        static float pressureKPaToBar(const float pressureKPa);
        static float pressureKPaToPsi(const float pressureKPa);
    };
}

#endif

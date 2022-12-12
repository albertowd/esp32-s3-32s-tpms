#include "TPMSConverters.h"

float TPMS::Converters::pressureKPaToBar(const float pressureKPa) {
    return pressureKPa / 100.0f;
}

float TPMS::Converters::pressureKPaToPsi(const float pressureKPa) {
    return pressureKPa * 0.1450377377f;
}

float TPMS::Converters::temperatureCToF(const float temperatureC) {
    return (temperatureC * 1.8f) + 32.0f;
}

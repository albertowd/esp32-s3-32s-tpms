#include "string"

#ifndef TPMS_H
#define TPMS_H

namespace TPMS {
    class Data {
        public:
            float temperatureC;
            float temperatureF;
            float pressureBar;
            float pressureKPa;
            float pressurePsi;
            std::string address;
            std::string manufacturer;
            uint8_t alarmFlags;
            uint8_t battery;

            Data();
            Data(const std::string hexData);
            ~Data();

            const std::string toString() const;
    };
}

#endif

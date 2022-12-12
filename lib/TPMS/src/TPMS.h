#include "string"

namespace TPMS {

    namespace BYTE_OFFSETS {
        const static size_t ADDRESS = 2;
        const static size_t ALARM_FLAGS = 17;
        const static size_t BATTERY = 16;
        const static size_t MANUFACTURER = 0;
        const static size_t PRESSURE = 8;
        const static size_t TEMPERATURE = 12;
    }

    namespace BYTE_SIZES {
        const static size_t ADDRESS = 6;
        const static size_t ALARM_FLAGS = 1;
        const static size_t BATTERY = 1;
        const static size_t DATA = 18;
        const static size_t PRESSURE = 4;
        const static size_t MANUFACTURER = 2;
        const static size_t TEMPERATURE = 4;
    }

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

            static float temperatureCToF(const float temperatureC);
            static float pressureKPaToBar(const float pressureKPa);
            static float pressureKPaToPsi(const float pressureKPa);

            static uint32_t readUInt32LE(const std::string buffer, size_t position);
            static uint8_t readUInt8(const std::string buffer, size_t position);
    };
}

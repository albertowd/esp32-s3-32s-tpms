#include "TPMS.h"

TPMS::Data::Data() :
    address(""),
    alarmFlags(0),
    battery(0),
    manufacturer(""),
    pressureBar(0),
    pressureKPa(0),
    pressurePsi(0),
    temperatureC(0),
    temperatureF(0) {}

TPMS::Data::Data(const std::string hexData) : TPMS::Data() {
    this->address = hexData.substr(TPMS::BYTE_OFFSETS::ADDRESS * 2, TPMS::BYTE_SIZES::ADDRESS * 2);
    this->alarmFlags = TPMS::Data::readUInt8(hexData, TPMS::BYTE_OFFSETS::ALARM_FLAGS);
    this->battery = TPMS::Data::readUInt8(hexData, TPMS::BYTE_OFFSETS::BATTERY);
    this->manufacturer = hexData.substr(TPMS::BYTE_OFFSETS::MANUFACTURER * 2, TPMS::BYTE_SIZES::MANUFACTURER * 2);
    this->pressureKPa = TPMS::Data::readUInt32LE(hexData, TPMS::BYTE_OFFSETS::PRESSURE) / 1000.0f;
    this->pressureBar = TPMS::Data::pressureKPaToBar(this->pressureKPa);
    this->pressurePsi = TPMS::Data::pressureKPaToPsi(this->pressureKPa);
    this->temperatureC = TPMS::Data::readUInt32LE(hexData, TPMS::BYTE_OFFSETS::TEMPERATURE) / 100.0f;
    this->temperatureF = TPMS::Data::temperatureCToF(this->temperatureC);
}

TPMS::Data::~Data() {}

const std::string TPMS::Data::toString() const {
    std::string info("Manufacturer: ");
    info += this->manufacturer;
    info += "\tAddress: ";
    info += this->address;
    info += "\tPressure: ";
    info += std::to_string(this->pressureBar);
    info += " bar - ";
    info += std::to_string(this->pressureKPa);
    info += " kPa ";
    info += std::to_string(this->pressurePsi);
    info += " psi\tTemperature: ";
    info += std::to_string(this->temperatureC);
    info += " ºC - ";
    info += std::to_string(this->temperatureF);
    info += " ºF\tBattery: ";
    info += std::to_string(this->battery);
    info += " %";
    if (this->alarmFlags) {
        info += "\tAlarm Flags: ";
        info += std::to_string(this->alarmFlags);
    }
    return info;
}

float TPMS::Data::pressureKPaToBar(const float pressureKPa) {
    return pressureKPa / 100.0f;
}

float TPMS::Data::pressureKPaToPsi(const float pressureKPa) {
    return pressureKPa * 0.1450377377f;
}

float TPMS::Data::temperatureCToF(const float temperatureC) {
    return (temperatureC * 1.8f) + 32.0f;
}

uint32_t TPMS::Data::readUInt32LE(const std::string buffer, size_t position) {
    return
        TPMS::Data::readUInt8(buffer, position) |
        TPMS::Data::readUInt8(buffer, position + 1) << 8 |
        TPMS::Data::readUInt8(buffer, position + 2) << 16 |
        TPMS::Data::readUInt8(buffer, position + 3) << 24;
}

uint8_t TPMS::Data::readUInt8(const std::string buffer, size_t position) {
    int offset(position * 2);
    char * restStr;
    if (offset + 2 <= buffer.length()) {
        return strtoul(buffer.substr(offset, 2).c_str(), &restStr, 16);
    } else {
        return 0U;
    }
}

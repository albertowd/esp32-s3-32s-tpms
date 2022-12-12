#include "TPMS.h"

#include "TPMSConverters.h"
#include "TPMSParser.h"
#include "TPMSUnits.h"

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
    this->alarmFlags = TPMS::Parser::readUInt8(hexData, TPMS::BYTE_OFFSETS::ALARM_FLAGS);
    this->battery = TPMS::Parser::readUInt8(hexData, TPMS::BYTE_OFFSETS::BATTERY);
    this->manufacturer = hexData.substr(TPMS::BYTE_OFFSETS::MANUFACTURER * 2, TPMS::BYTE_SIZES::MANUFACTURER * 2);
    this->pressureKPa = TPMS::Parser::readUInt32LE(hexData, TPMS::BYTE_OFFSETS::PRESSURE) / 1000.0f;
    this->pressureBar = TPMS::Converters::pressureKPaToBar(this->pressureKPa);
    this->pressurePsi = TPMS::Converters::pressureKPaToPsi(this->pressureKPa);
    this->temperatureC = TPMS::Parser::readUInt32LE(hexData, TPMS::BYTE_OFFSETS::TEMPERATURE) / 100.0f;
    this->temperatureF = TPMS::Converters::temperatureCToF(this->temperatureC);
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

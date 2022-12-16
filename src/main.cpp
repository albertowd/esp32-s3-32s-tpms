#include <Arduino.h>
#include <FS.h>
#include <NimBLEDevice.h>
#include <WiFi.h>

#include <RGBLEDColors.h>
#include <RGBLEDControl.h>
#include <RC3Entry.h>
#include <SocketServer.h>
#include <TPMS.h>
#include <TPMSUnits.h>

#ifndef SOCKET_SERVER_PORT
#define SOCKET_SERVER_PORT 5000
#endif

NimBLEScan *pBLEScan(nullptr);
RC3::Entry entry;
SocketServer socketServer(SOCKET_SERVER_PORT);

const RC3::AnalogIndexes analogStart(RC3::A1);
const char *wifiSSID("Cyberia");
const char *wifiPassword("serial000");

class TPMSDeviceCallbacks : public NimBLEAdvertisedDeviceCallbacks
{
    void onResult(NimBLEAdvertisedDevice *advertisedDevice)
    {
        if (0 == advertisedDevice->getName().substr(0U, 4U).compare("TPMS"))
        {
            const std::string manData(advertisedDevice->getManufacturerData());
            char *hexBuffer(NimBLEUtils::buildHexData(nullptr, (uint8_t *)manData.data(), manData.length()));
            const std::string hexData(hexBuffer, TPMS::BYTE_SIZES::DATA * 2U);
            delete hexBuffer;
            TPMS::Data data(hexData);
            // Serial.printf("Sensor %s\t%s\n", advertisedDevice->getName().c_str(), data.toString().c_str());

            const int prefix(atoi(advertisedDevice->getName().substr(4U, 1U).c_str()) - 1);
            entry.setAnalog(static_cast<RC3::AnalogIndexes>(static_cast<int>(analogStart) + (prefix * 2)), data.pressureKPa);
            entry.setAnalog(static_cast<RC3::AnalogIndexes>(static_cast<int>(analogStart) + (prefix * 2) + 1), data.temperatureC);
            // entry.setAnalog(static_cast<RC3::AnalogIndexes>(static_cast<int>(analogStart) + (prefix * 3) + 2), data.battery);
        }
    }
};

void setup()
{
    Serial.begin(115200);
    RGBLED::Control::getSingleton()->toggle(true);

    Serial.printf("Connecting to WiFi %s...\n", wifiSSID);
    WiFi.begin(wifiSSID, wifiPassword);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi..");
    }
    Serial.printf("Wifi connected with IP: %s\n", WiFi.localIP().toString().c_str());
    RGBLED::Control::getSingleton()->setColor(RGBLED::Colors::BLUE);

    socketServer.initServer();
    Serial.println("Waiting for first client to connect...");
    socketServer.accetFirstClient();
    RGBLED::Control::getSingleton()->setColor(RGBLED::Colors::GREEN);

    NimBLEDevice::setScanDuplicateCacheSize(10);
    NimBLEDevice::setScanFilterMode(CONFIG_BTDM_SCAN_DUPL_TYPE_DEVICE);
    NimBLEDevice::init("Alberto NodeMCU");

    pBLEScan = NimBLEDevice::getScan();
    pBLEScan->setAdvertisedDeviceCallbacks(new TPMSDeviceCallbacks(), false);
    pBLEScan->setActiveScan(true);
    pBLEScan->setInterval(200);
    pBLEScan->setMaxResults(0);
    pBLEScan->setWindow(50);
}

void loop()
{
    if (RGBLED::Control::getSingleton()->getColor().green == RGBLED::Colors::GREEN.green) {
        RGBLED::Control::getSingleton()->toggle(false);
    } else {
        RGBLED::Control::getSingleton()->setColor(RGBLED::Colors::GREEN);
    }

    if (pBLEScan->isScanning() == false)
    {
        pBLEScan->start(0, nullptr, false);
    }

    socketServer.writeToClient(entry.pack());
    entry.updateId();

    delay(500);
}

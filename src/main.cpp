#include <Arduino.h>
#include <FS.h>
#include <NimBLEDevice.h>
#include <WiFi.h>

#include "RC3Entry.h"
#include "SocketServer.h"
#include "TPMS.h"
#include "TPMSUnits.h"

#ifdef ENABLE_TPMS_RGB
#include "RGBLEDColors.h"
#include "RGBLEDControl.h"
#endif

#ifdef ENABLE_TPMS_DISPLAY
#include "TPMSDisplay.h"
#include "TPMSDisplaySocketServer.h"
#include "TPMSDisplayTyre.h"
#include "TPMSDisplayWiFi.h"
#endif

#ifndef SOCKET_SERVER_PORT
#define SOCKET_SERVER_PORT 5000
#endif

#ifndef DEFAULT_WIFI_SSID
#define DEFAULT_WIFI_SSID "Cyberia"
#endif

#ifndef DEFAULT_WIFI_PASSWORD
#define DEFAULT_WIFI_PASSWORD "serial000"
#endif

NimBLEScan *pBLEScan(nullptr);
RC3::Entry entry;
SocketServer *socketServer(nullptr);

const RC3::AnalogIndexes analogStart(RC3::A1);

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
            Serial.printf("Sensor %s\t%s\n", advertisedDevice->getName().c_str(), data.toString().c_str());

            const int prefix(atoi(advertisedDevice->getName().substr(4U, 1U).c_str()) - 1);
            entry.setAnalog(static_cast<RC3::AnalogIndexes>(static_cast<int>(analogStart) + (prefix * 2)), data.pressureKPa);
            entry.setAnalog(static_cast<RC3::AnalogIndexes>(static_cast<int>(analogStart) + (prefix * 2) + 1), data.temperatureC);
            // entry.setAnalog(static_cast<RC3::AnalogIndexes>(static_cast<int>(analogStart) + (prefix * 3) + 2), data.battery);
        }
    }
};

void connectToWifi()
{
#ifdef ENABLE_TPMS_RGB
    RGBLED::Control::getSingleton()->setColor(RGBLED::Colors::BLUE);
#endif
#ifdef ENABLE_TPMS_DISPLAY
    TPMSDisplay::WiFi::render(DEFAULT_WIFI_SSID);
#endif
    Serial.printf("Connecting to WiFi %s...\n", DEFAULT_WIFI_SSID);

    WiFi.begin(DEFAULT_WIFI_SSID, DEFAULT_WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi..");
    }
    Serial.printf("Wifi connected with IP: %s\n", WiFi.localIP().toString().c_str());

#ifdef ENABLE_TPMS_DISPLAY
    TPMSDisplay::Base::renderBlack();
#endif
}

void waitForConnection()
{
    if (nullptr != socketServer)
    {
        delete socketServer;
    }

    std::string address(WiFi.localIP().toString().c_str());
    address.append(":").append(std::to_string(SOCKET_SERVER_PORT));

#ifdef ENABLE_TPMS_RGB
    RGBLED::Control::getSingleton()->setColor(RGBLED::Colors::GREEN);
#endif
#ifdef ENABLE_TPMS_DISPLAY
    TPMSDisplay::SocketServer::render(address.c_str());
#endif
    Serial.println("Waiting for client to connect...");

    socketServer = new SocketServer(SOCKET_SERVER_PORT);
    socketServer->accetFirstClient();

#ifdef ENABLE_TPMS_DISPLAY
    TPMSDisplay::Base::renderBlack();
#endif
}

void setup()
{
    Serial.begin(115200);

#ifdef ENABLE_TPMS_RGB
    RGBLED::Control::getSingleton()->toggle(true);
#endif
#ifdef ENABLE_TPMS_DISPLAY
    TPMSDisplay::Base::begin();
    TPMSDisplay::Base::renderBoot();
#endif

    connectToWifi();

    // TODO: wait for a button press
    // waitForConnection();

    NimBLEDevice::setScanDuplicateCacheSize(10);
    NimBLEDevice::setScanFilterMode(CONFIG_BTDM_SCAN_DUPL_TYPE_DEVICE);
    NimBLEDevice::init("RC TPMS");

    pBLEScan = NimBLEDevice::getScan();
    pBLEScan->setAdvertisedDeviceCallbacks(new TPMSDeviceCallbacks(), false);
    pBLEScan->setActiveScan(true);
    pBLEScan->setInterval(200);
    pBLEScan->setMaxResults(0);
    pBLEScan->setWindow(50);
}

void loop()
{
#ifdef ENABLE_TPMS_RGB
    if (RGBLED::Control::getSingleton()->getColor().green == RGBLED::Colors::GREEN.green)
    {
        RGBLED::Control::getSingleton()->toggle(false);
    }
    else
    {
        RGBLED::Control::getSingleton()->setColor(RGBLED::Colors::GREEN);
    }
#endif

    if (pBLEScan->isScanning() == false)
    {
        pBLEScan->start(0, nullptr, false);
    }

    if (socketServer) {
        socketServer->writeToClient(entry.pack());
        entry.updateId();
    }

#ifdef ENABLE_TPMS_DISPLAY
    TPMSDisplay::Tyre::renderFL(entry.getAnalog(RC3::A1), entry.getAnalog(RC3::A2));
    TPMSDisplay::Tyre::renderFR(entry.getAnalog(RC3::A3), entry.getAnalog(RC3::A4));
    TPMSDisplay::Tyre::renderRL(entry.getAnalog(RC3::A5), entry.getAnalog(RC3::A6));
    TPMSDisplay::Tyre::renderRR(entry.getAnalog(RC3::A7), entry.getAnalog(RC3::A8));
#endif

    delay(500);
}

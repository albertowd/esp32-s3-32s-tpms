#include <Arduino.h>
#include <NimBLEDevice.h>

#include <TPMS.h>
#include <TPMSUnits.h>

NimBLEScan* pBLEScan;

class TPMSDeviceCallbacks: public NimBLEAdvertisedDeviceCallbacks {
    void onResult(NimBLEAdvertisedDevice* advertisedDevice) {
      if (0 == advertisedDevice->getName().substr(0, 4).compare("TPMS")) {
        const std::string manData(advertisedDevice->getManufacturerData());
        char * hexBuffer(NimBLEUtils::buildHexData(nullptr, (uint8_t *)manData.data(), manData.length()));
        const std::string hexData(hexBuffer, TPMS::BYTE_SIZES::DATA * 2U);
        delete hexBuffer;
        TPMS::Data data(hexData);
        Serial.println(data.toString().c_str());
      }
    }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Scanning...");
  
  NimBLEDevice::setScanDuplicateCacheSize(10);
  NimBLEDevice::setScanFilterMode(CONFIG_BTDM_SCAN_DUPL_TYPE_DEVICE);
  NimBLEDevice::init("");

  pBLEScan = NimBLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new TPMSDeviceCallbacks(), false);
  pBLEScan->setActiveScan(true); // Set active scanning, this will get more data from the advertiser.
  pBLEScan->setInterval(97); // How often the scan occurs / switches channels; in milliseconds,
  pBLEScan->setMaxResults(0); // do not store the scan results, use callback only.
  pBLEScan->setWindow(37);  // How long to scan during the interval; in milliseconds.
}

void loop() {
  if(pBLEScan->isScanning() == false) {
      pBLEScan->start(0, nullptr, false);
  }

  delay(1000);
}

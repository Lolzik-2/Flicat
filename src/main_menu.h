#pragma once
#include "ui.h"
#include <M5Cardputer.h>

class MainMenu {
public:
    MainMenu();
    void begin();
private:
    void drawMenu();
    int selectedIndex = 0;
    int totalItems = 4;
    const char* items[4] = {"WiFi", "BLE", "IR", "Settings"};
};

#include "main_menu.h"
#include "wifi/wifi_scanner.h"
#include "ble/ble_spam.h"
#include "ir/ir_jammer.h"

MainMenu::MainMenu() {}

void MainMenu::begin() {
    M5Cardputer.Display.fillScreen(THEME_BG);
    drawMenu();
    while (true) {
        M5Cardputer.update();
        if (M5Cardputer.Keyboard.isKeyPressed(';')) {
            selectedIndex = (selectedIndex - 1 + totalItems) % totalItems;
            drawMenu();
            delay(150);
        }
        if (M5Cardputer.Keyboard.isKeyPressed('.')) {
            selectedIndex = (selectedIndex + 1) % totalItems;
            drawMenu();
            delay(150);
        }
        if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER)) {
            switch (selectedIndex) {
                case 0: runWifiScanner(); break;
                case 1: runBleSpam(); break;
                case 2: runIrJammer(); break;
                case 3: /* Settings */ break;
            }
            M5Cardputer.Display.fillScreen(THEME_BG);
            drawMenu();
            delay(200);
        }
        delay(10);
    }
}

void MainMenu::drawMenu() {
    auto& display = M5Cardputer.Display;
    display.fillScreen(THEME_BG);
    display.setTextColor(THEME_FG, THEME_BG);
    display.setTextSize(2);
    display.setCursor(10, 10);
    display.println("FLICAT");
    for (int i = 0; i < totalItems; i++) {
        int y = 50 + i * 30;
        if (i == selectedIndex) {
            display.fillRect(5, y - 2, display.width() - 10, 28, THEME_HIGHLIGHT);
            display.setTextColor(THEME_BG, THEME_HIGHLIGHT);
        } else {
            display.setTextColor(THEME_FG, THEME_BG);
        }
        display.setCursor(15, y);
        display.print(items[i]);
    }
    display.setTextSize(1);
    display.setTextColor(THEME_ACCENT, THEME_BG);
    display.setCursor(10, display.height() - 15);
    display.println("Up/Down: Select | Enter: Open");
}

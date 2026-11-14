#include "wifi_scanner.h"
#include "wifi_deauth.h"
#include "../ui.h"
#include <WiFi.h>

void runWifiScanner() {
    auto& display = M5Cardputer.Display;
    display.fillScreen(THEME_BG);
    display.setTextColor(THEME_FG, THEME_BG);
    display.setTextSize(2);
    display.setCursor(10, 10);
    display.println("Scanning WiFi...");
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
    int n = WiFi.scanNetworks();
    if (n == 0) { display.setCursor(10, 50); display.println("No networks"); delay(2000); return; }
    int sel = 0;
    while (true) {
        display.fillScreen(THEME_BG);
        display.setTextSize(2); display.setCursor(10, 10); display.println("Select Target:");
        display.setTextSize(1);
        for (int i = 0; i < n; i++) {
            int y = 40 + i * 15;
            if (i == sel) { display.fillRect(5, y - 2, display.width() - 10, 17, THEME_HIGHLIGHT); display.setTextColor(THEME_BG, THEME_HIGHLIGHT); }
            else display.setTextColor(THEME_FG, THEME_BG);
            display.setCursor(10, y);
            display.print(WiFi.SSID(i).substring(0, 20));
            display.print(" ("); display.print(WiFi.RSSI(i)); display.println(" dBm)");
        }
        M5Cardputer.update();
        if (M5Cardputer.Keyboard.isKeyPressed(';')) { sel = (sel - 1 + n) % n; delay(150); }
        if (M5Cardputer.Keyboard.isKeyPressed('.')) { sel = (sel + 1) % n; delay(150); }
        if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER)) break;
        if (M5Cardputer.Keyboard.isKeyPressed('`')) return;
        delay(10);
    }
    startDeauth(WiFi.SSID(sel).c_str(), WiFi.BSSID(sel), WiFi.channel(sel));
}

#include "ir_jammer.h"
#include "../ui.h"
#include <IRsend.h>
#define IR_LED_PIN 44

void runIrJammer() {
    auto& display = M5Cardputer.Display;
    display.fillScreen(THEME_BG);
    display.setTextColor(THEME_FG, THEME_BG);
    display.setTextSize(2); display.setCursor(10, 10); display.println("IR Jammer");
    display.setTextSize(1); display.setCursor(10, 50); display.println("Sending 38kHz noise...");
    
    IRsend irsend(IR_LED_PIN);
    irsend.begin();
    while (true) {
        M5Cardputer.update();
        if (M5Cardputer.Keyboard.isKeyPressed('`')) break;
        for (int i = 0; i < 100; i++) {
            irsend.mark(10);
            irsend.space(10);
            delayMicroseconds(20);
        }
        delay(1);
    }
    display.fillScreen(THEME_BG); display.setCursor(10, 50); display.println("Stopped"); delay(500);
}

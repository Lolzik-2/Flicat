#include "ir_tvbgone.h"
#include "../ui.h"
#include <IRsend.h>
#define IR_LED_PIN 44

const uint32_t tvCodes[] = {0x20DF10EF, 0xE0E040BF, 0x10EF};
const int numCodes = 3;

void runTvBGone() {
    auto& display = M5Cardputer.Display;
    display.fillScreen(THEME_BG);
    display.setTextColor(THEME_FG, THEME_BG);
    display.setTextSize(2); display.setCursor(10, 10); display.println("TV-B-Gone");
    display.setTextSize(1); display.setCursor(10, 50); display.println("Sending codes...");
    
    IRsend irsend(IR_LED_PIN);
    irsend.begin();
    for (int i = 0; i < numCodes; i++) {
        irsend.sendNEC(tvCodes[i], 32);
        delay(200);
    }
    display.setCursor(10, 80); display.println("Done"); delay(1000);
}

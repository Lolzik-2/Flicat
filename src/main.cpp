#include <M5Cardputer.h>
#include "main_menu.h"

MainMenu mainMenu;

void setup() {
    auto cfg = M5.config();
    M5Cardputer.begin(cfg, true);
    M5Cardputer.Display.setRotation(1);
    mainMenu.begin();
}

void loop() {}

#include "trellis.h"

Trellis::Trellis()
    : seesaw(ADDR), pixels(seesaw, NEOPIXEL_PIN, NEOPIXEL_LENGTH), keypad(seesaw) {} ;

void Trellis::init() {
    pixels.init();
    keypad.init();
}
#include "trellis.h"

Trellis::Trellis()
    : seesaw(ADDR), pixels(seesaw, NEOPIXEL_PIN, NEOPIXEL_LENGTH) {} ;

void Trellis::init() {
    pixels.init();
}
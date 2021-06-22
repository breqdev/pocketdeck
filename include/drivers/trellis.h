#pragma once

#include "main.h"
#include "drivers/seesaw.h"
#include "drivers/neopixel.h"
#include "drivers/keypad.h"


class Trellis {
    private:
        static const int ADDR = 0x2E;
        static const int NEOPIXEL_PIN = 3;
        static const int NEOPIXEL_LENGTH = 16;

        Seesaw seesaw;
    public:
        Trellis();

        void init();

        NeoPixel pixels;
        Keypad keypad;
};
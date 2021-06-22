#pragma once

#include "main.h"
#include "seesaw.h"
#include "neopixel.h"
#include "keypad.h"


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
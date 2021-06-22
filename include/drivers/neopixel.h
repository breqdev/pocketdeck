#pragma once

#include "drivers/seesaw.h"


class NeoPixel {
    private:
        static const int MODULE_BASE = 0x0E;

        enum Functions {
            PIN = 0x01,
            SPEED = 0x02,
            BUF_LENGTH = 0x03,
            BUF = 0x04,
            SHOW = 0x05
        };

        uint8_t pin;
        uint16_t strand_length;

        Seesaw& seesaw;

    public:
        NeoPixel(Seesaw& seesaw, uint8_t pin, uint16_t strand_length);

        void init();
        void set(uint16_t number, uint8_t r, uint8_t g, uint8_t b);
        void show();
};

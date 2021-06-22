#pragma once

#include "seesaw.h"


class Keypad {
    private:
        static const int MODULE_BASE = 0x10;

        enum Functions {
            STATUS = 0x00,
            EVENT = 0x01,
            INTENSET = 0x02,
            INTENCLR = 0x03,
            COUNT = 0x04,
            FIFO = 0x10
        };

        Seesaw& seesaw;

        constexpr uint8_t key_trellis_to_seesaw(uint8_t key) {
            return (key % 4) + (key / 4) * 8;
        };
        constexpr uint8_t key_seesaw_to_trellis(uint8_t key) {
            return (key % 8) + (key / 8) * 4;
        };

    public:
        enum Edge {
            HIGH = 0,
            LOW,
            FALLING,
            RISING
        };

        Keypad(Seesaw& seesaw);

        void init();

        uint8_t* events(uint8_t& count);
};

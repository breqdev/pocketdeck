#pragma once

#include "main.h"

#include <algorithm>

class Seesaw {
    private:
        static const uint8_t HEADER_LENGTH = 2;

        uint8_t address;

        uint8_t* add_header(uint8_t module_base, uint8_t module_function, uint8_t* data, size_t length);

    public:
        Seesaw(uint8_t address);

        void write(uint8_t module_base, uint8_t module_function, uint8_t* data, size_t length);
        void read(uint8_t module_base, uint8_t module_function, uint8_t* data, size_t length, uint16_t delay);
};

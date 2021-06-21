#pragma once

#include "main.h"

#include <algorithm>

#include "pico/binary_info.h"
#include "hardware/i2c.h"


#define SEESAW_MESSAGE_HEADER_LENGTH 2

uint8_t* seesaw_make_header(uint8_t module_base, uint8_t module_function, uint8_t* data, size_t length) {
    size_t buflen = length + SEESAW_MESSAGE_HEADER_LENGTH;
    uint8_t* buffer = new uint8_t[buflen];

    buffer[0] = module_base;
    buffer[1] = module_function;

    std::copy(data, data + length, buffer + SEESAW_MESSAGE_HEADER_LENGTH);

    return buffer;
}

void seesaw_write(uint8_t seesaw_addr, uint8_t module_base, uint8_t module_function, uint8_t* data, size_t length) {
    uint8_t* buffer = seesaw_make_header(module_base, module_function, data, length);

    i2c_write_blocking(
        FEATHER_I2C,
        seesaw_addr,
        buffer,
        length + SEESAW_MESSAGE_HEADER_LENGTH,
        false
    );

    delete[] buffer;
}

void seesaw_read(uint8_t seesaw_addr, uint8_t module_base, uint8_t module_function, uint8_t* data, size_t length, uint16_t delay) {
    uint8_t header[] = {module_base, module_function};

    i2c_write_blocking(
        FEATHER_I2C,
        seesaw_addr,
        header,
        2,
        false
    );

    sleep_ms(delay);

    i2c_read_blocking(
        FEATHER_I2C,
        seesaw_addr,
        data,
        length,
        false
    );
}
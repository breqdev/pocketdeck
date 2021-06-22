#include "neopixel.h"


NeoPixel::NeoPixel(Seesaw& seesaw, uint8_t pin, uint16_t strand_length)
    : seesaw(seesaw), pin(pin), strand_length(strand_length) {};


void NeoPixel::init() {
    uint8_t pin_select_data[] = {pin};

    seesaw.write(
        MODULE_BASE,
        PIN,
        pin_select_data,
        1
    );

    uint16_t buffer_length = 3 * strand_length;
    uint8_t buf_length_data[] = {(buffer_length >> 8), buffer_length};

    seesaw.write(
        MODULE_BASE,
        BUF_LENGTH,
        buf_length_data,
        2
    );
}


void NeoPixel::set(uint16_t number, uint8_t r, uint8_t g, uint8_t b) {
    uint8_t data[] = {(number >> 8), (number & 0xff), g, r, b};

    seesaw.write(
        MODULE_BASE,
        BUF,
        data,
        5
    );
}


void NeoPixel::show() {
    seesaw.write(
        MODULE_BASE,
        SHOW,
        nullptr,
        0
    );
}
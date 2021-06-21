#pragma once

#include "main.h"
#include "seesaw.h"

#define TRELLIS_ADDR 0x2E

#define NEOPIXEL_MODULE_BASE 0x0E

#define NEOPIXEL_FUNCTION_PIN 0x01
#define NEOPIXEL_FUNCTION_SPEED 0x01
#define NEOPIXEL_FUNCTION_BUF_LENGTH 0x03
#define NEOPIXEL_FUNCTION_BUF 0x04
#define NEOPIXEL_FUNCTION_SHOW 0x05

#define NEOTRELLIS_NEOPIXEL_PIN 3
#define NEOTRELLIS_NEOPIXEL_LENGTH 16
#define NEOTRELLIS_NEOPIXEL_TYPE 3 // rgb, not rgbw
#define NEOTRELLIS_NEOPIXEL_BUF_LENGTH NEOTRELLIS_NEOPIXEL_LENGTH * NEOTRELLIS_NEOPIXEL_TYPE

void trellis_neopixel_init() {
    uint8_t pin_select_data[] = {NEOTRELLIS_NEOPIXEL_PIN};

    printf("writing pin select\n");

    seesaw_write(
        TRELLIS_ADDR,
        NEOPIXEL_MODULE_BASE,
        NEOPIXEL_FUNCTION_PIN,
        pin_select_data,
        1
    );

    printf("wrote pin select\n");
    sleep_ms(500);

    uint8_t buf_length_data[] = {0, NEOTRELLIS_NEOPIXEL_BUF_LENGTH};

    seesaw_write(
        TRELLIS_ADDR,
        NEOPIXEL_MODULE_BASE,
        NEOPIXEL_FUNCTION_BUF_LENGTH,
        buf_length_data,
        2
    );
}

void trellis_neopixel_set(uint16_t address, uint8_t r, uint8_t g, uint8_t b) {
    uint8_t data[] = {(address >> 8), (address & 0xff), g, r, b};

    seesaw_write(
        TRELLIS_ADDR,
        NEOPIXEL_MODULE_BASE,
        NEOPIXEL_FUNCTION_BUF,
        data,
        5
    );
}

void trellis_neopixel_show() {
    seesaw_write(
        TRELLIS_ADDR,
        NEOPIXEL_MODULE_BASE,
        NEOPIXEL_FUNCTION_SHOW,
        nullptr,
        0
    );
}
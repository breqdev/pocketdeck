#include "drivers/display.h"

#include <stdio.h>
#include <algorithm>

const uint8_t Display::startup[] = {
    ON_OFF | 0,
    START_LINE, 0,
    CONTRAST, 0x2f,
    ADDRESS_MODE | 0,
    SEGMENT_REMAP | 0,
    COM_SCAN_DIR | 0xF,
    MULTIPLEX, 0x7F,
    OFFSET, 0x60,
    INTERNAL_CLOCK, 0x51,
    DISCHARGE_PRECHARGE, (2) << 4 + (2),
    VCOM_DESELECT, 0x35,
    PAGE_ADDR | 0,
    ENTIRE_DISPLAY_ON | 0,
    REVERSE | 0,
    ON_OFF | 1
};


Display::Display() {

}


void Display::send_command(uint8_t command) {
    uint8_t data[] = {0x80, command};

    i2c_write_blocking(
        FEATHER_I2C,
        ADDR,
        data,
        2,
        false
    );
}


void Display::send_data(const uint8_t* data, size_t length) {
    uint8_t* buffer = new uint8_t[length + 1];

    std::copy(data, data + length, buffer + 1);
    buffer[0] = 0x40;

    i2c_write_blocking(
        FEATHER_I2C,
        ADDR,
        buffer,
        length + 1,
        false
    );
}


void Display::init() {
    for (uint8_t command : startup) {
        printf("sending command %02x\n", command);
        send_command(command);
    }
}

void Display::verify_connection() {
    uint8_t command = 0x80;
    uint8_t response = 0;

    i2c_write_blocking(
        FEATHER_I2C,
        ADDR,
        &command,
        1,
        false
    );

    i2c_read_blocking(
        FEATHER_I2C,
        ADDR,
        &response,
        1,
        false
    );

    printf("response: %08b\n", response);
}

void Display::flash() {
    send_command(REVERSE | 1);
    sleep_ms(100);
    send_command(REVERSE | 0);
    sleep_ms(100);
}

void Display::draw(const uint8_t* bitmap) {
    uint16_t chunk_size = 16;

    for (int page = 0; page <= (HEIGHT / 8); ++page) {
        send_command(PAGE_ADDR | page);
        send_command(COL_ADDR_LOW | 0);
        send_command(COL_ADDR_HIGH | 0);

        for (int column = 0; column < WIDTH; ++column) {
            send_command(COL_ADDR_LOW | (column & 0x0F));
            send_command(COL_ADDR_HIGH | (column >> 4));

            // send_data(bitmap + (page * WIDTH) + column, 1);
            uint8_t dummy = 0xFF;
            send_data(&dummy, 1);
        }
    }
}
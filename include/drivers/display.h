#include "main.h"


class Display {
    private:
        enum Command {
            COL_ADDR_LOW = 0x00,
            COL_ADDR_HIGH = 0x10,
            ADDRESS_MODE = 0x20,
            CONTRAST = 0x81,
            SEGMENT_REMAP = 0xA0,
            MULTIPLEX = 0xA8,
            ENTIRE_DISPLAY_ON = 0xA4,
            REVERSE = 0xA6,
            OFFSET = 0xD3,
            DC_DC = 0xAD,
            ON_OFF = 0xAE,
            PAGE_ADDR = 0xB0,
            COM_SCAN_DIR = 0xC0,
            INTERNAL_CLOCK = 0xD5,
            DISCHARGE_PRECHARGE = 0xD9,
            VCOM_DESELECT = 0xDB,
            START_LINE = 0xDC,
            READ_MODIFY_WRITE = 0xE0,
            READ_MODIFY_WRITE_END = 0xEE,
            NOP = 0xE3,
        };

        static const uint8_t ADDR = 0x3C;

        static const uint8_t WIDTH = 64;
        static const uint8_t HEIGHT = 128;

        static const uint8_t PAGES = HEIGHT / 8;
        static const uint8_t BYTES_PER_PAGE = WIDTH;

        const static uint8_t startup[];

        void send_command(uint8_t command);
        void send_data(const uint8_t* data, size_t length);

    public:
        Display();

        void init();

        void flash();

        void draw(const uint8_t* bitmap);

        void verify_connection();
};
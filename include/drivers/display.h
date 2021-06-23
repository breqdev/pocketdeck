#include "main.h"


namespace Display {
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

    static const uint8_t WIDTH = 128;
    static const uint8_t HEIGHT = 64;

    static const uint8_t PAGES = 16;
    static const uint16_t BYTES_PER_PAGE = 64;

    static const uint16_t TICK_INTERVAL = 5;

    const uint8_t startup[] = {
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

    static const uint16_t BUFFER_SIZE = WIDTH * HEIGHT / 8;

    static lv_disp_draw_buf_t disp_buf;
    static lv_color_t buf_1[BUFFER_SIZE];

    static lv_disp_drv_t disp_drv;

    static lv_disp_t* disp;

    static repeating_timer_t timer;

    void send_command(uint8_t command);
    void send_data(const uint8_t* data, size_t length);

    bool do_tick(repeating_timer_t* rt);

    void init();
    void flush(lv_disp_drv_t* disp_drv, const lv_area_t* area, lv_color_t* color_p);
    void round(lv_disp_drv_t* disp_drv, lv_area_t* area);
    void set_pixel(lv_disp_drv_t* disp_drv, uint8_t* buf, lv_coord_t buf_w, lv_coord_t x, lv_coord_t y, lv_color_t color, lv_opa_t opa);
};
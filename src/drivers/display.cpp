#include "drivers/display.h"

#include <stdio.h>
#include <cstring>


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

    std::memcpy(buffer + 1, data, length);
    buffer[0] = 0x40;

    i2c_write_blocking(
        FEATHER_I2C,
        ADDR,
        buffer,
        length + 1,
        false
    );

    delete[] buffer;
}


bool Display::do_tick(repeating_timer_t* rt) {
    lv_tick_inc(Display::TICK_INTERVAL);
    return true;
}


void Display::init() {
    for (uint8_t command : startup) {
        send_command(command);
    }

    lv_init();

    lv_disp_draw_buf_init(&disp_buf, buf_1, nullptr, WIDTH * HEIGHT);

    lv_disp_drv_init(&disp_drv);

    disp_drv.hor_res = WIDTH;
    disp_drv.ver_res = HEIGHT;

    disp_drv.flush_cb = flush;
    disp_drv.rounder_cb = round;
    disp_drv.set_px_cb = set_pixel;

    disp_drv.draw_buf = &disp_buf;

    disp = lv_disp_drv_register(&disp_drv);
}

void Display::set_pixel(lv_disp_drv_t* disp_drv, uint8_t* buf, lv_coord_t buf_w, lv_coord_t x, lv_coord_t y, lv_color_t color, lv_opa_t opa) {
    uint16_t page = x >> 3;
    uint16_t column = y;
    uint8_t bit = x & 0x7;

    uint8_t mask = 1 << bit;

    uint16_t bytes_per_page = disp_buf.area.y2 - disp_buf.area.y1 + 1;

    uint16_t buffer_index = (page * bytes_per_page) + column;

    if (color.full == 0) {
        buf[buffer_index] |= mask;
    } else {
        buf[buffer_index] &= ~mask;
    }
}

void Display::round(lv_disp_drv_t* disp_drv, lv_area_t* area) {
    area->x1 = area->x1 & ~0x7;
    area->x2 = (area->x2 & ~0x7) + 7;
}

void Display::flush(lv_disp_drv_t* disp_drv, const lv_area_t* area, lv_color_t* color_p) {
    uint8_t start_page = area->x1 >> 3;
    uint8_t end_page = area->x2 >> 3;

    uint8_t start_col = area->y1;
    uint8_t end_col = area->y2 + 1;

    uint8_t start_col_high = (start_col >> 4) & 0x7;
    uint8_t start_col_low = start_col & 0xF;

    uint8_t bytes_per_page = end_col - start_col;

    uint8_t* color_buffer = reinterpret_cast<uint8_t*>(color_p);
    for (uint8_t page_offset = 0; start_page + page_offset <= end_page; ++page_offset) {
        send_command(PAGE_ADDR | start_page + page_offset);

        send_command(COL_ADDR_LOW | start_col_low);
        send_command(COL_ADDR_HIGH | start_col_high);

        uint16_t buffer_index = page_offset * bytes_per_page;
        uint8_t* data = color_buffer + buffer_index;

        send_data(data, bytes_per_page);
    }

    lv_disp_flush_ready(disp_drv);
}
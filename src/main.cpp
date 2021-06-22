#include <stdio.h>
#include "main.h"
#include "drivers/trellis.h"

void i2c_setup() {
    i2c_init(FEATHER_I2C, 100 * 1000);

    gpio_set_function(FEATHER_SDA, GPIO_FUNC_I2C);
    gpio_set_function(FEATHER_SCL, GPIO_FUNC_I2C);

    gpio_pull_up(FEATHER_SDA);
    gpio_pull_up(FEATHER_SCL);
}


Trellis trellis;

int main() {
    stdio_init_all();

    sleep_ms(2000);
    printf("setting up trellis\n");

    i2c_setup();
    trellis.init();

    // while (true) {
    //     trellis.pixels.set(0, 255, 255, 255);
    //     trellis.pixels.show();
    //     sleep_ms(500);

    //     trellis.pixels.set(0, 255, 0, 0);
    //     trellis.pixels.show();
    //     sleep_ms(500);

    //     trellis.pixels.set(0, 0, 255, 0);
    //     trellis.pixels.show();
    //     sleep_ms(500);

    //     trellis.pixels.set(0, 0, 0, 255);
    //     trellis.pixels.show();
    //     sleep_ms(500);
    // }

    sleep_ms(2000);
    printf("ready!\n");

    while (true) {
        uint8_t event_count;
        uint8_t* events = trellis.keypad.events(event_count);

        for (int i = 0; i < event_count; ++i) {
            uint8_t event = events[i];

            uint8_t key = (event >> 2);
            Keypad::Edge edge = static_cast<Keypad::Edge>(event & 0x03);

            printf("Event %01d received on key %02d\n", edge, key);

            if (edge == Keypad::RISING) {
                trellis.pixels.set(key, 255, 255, 255);
            } else {
                trellis.pixels.set(key, 0, 0, 0);
            }
        }

        if (event_count) {
            trellis.pixels.show();
        }

        delete[] events;

        sleep_ms(20);
    }

    return 0;
}

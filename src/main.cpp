#include <stdio.h>
#include "pico/stdlib.h"
#include "main.h"
#include "i2c.h"
#include "trellis.h"

int main() {
    stdio_init_all();

    printf("IO OK!\n");

    sleep_ms(2000);

    printf("Attempt I2C setup\n");

    i2c_setup();

    printf("I2C OK!\n");

    sleep_ms(500);

    printf("Attempt NeoPixel Setup\n");

    trellis_neopixel_init();

    printf("TRELLIS OK!\n");

    while (true) {
        trellis_neopixel_set(0, 255, 255, 255);
        trellis_neopixel_show();
        sleep_ms(500);

        trellis_neopixel_set(0, 255, 0, 0);
        trellis_neopixel_show();
        sleep_ms(500);

        trellis_neopixel_set(0, 0, 255, 0);
        trellis_neopixel_show();
        sleep_ms(500);

        trellis_neopixel_set(0, 0, 0, 255);
        trellis_neopixel_show();
        sleep_ms(500);
    }
    return 0;
}

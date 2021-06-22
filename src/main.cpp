#include <stdio.h>
#include "main.h"
#include "trellis.h"

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

    printf("IO OK!\n");

    sleep_ms(2000);

    printf("Attempt I2C setup\n");

    i2c_setup();

    printf("I2C OK!\n");

    sleep_ms(500);

    printf("Attempt NeoPixel Setup\n");

    trellis.init();

    printf("TRELLIS OK!\n");

    while (true) {
        trellis.pixels.set(0, 255, 255, 255);
        trellis.pixels.show();
        sleep_ms(500);

        trellis.pixels.set(0, 255, 0, 0);
        trellis.pixels.show();
        sleep_ms(500);

        trellis.pixels.set(0, 0, 255, 0);
        trellis.pixels.show();
        sleep_ms(500);

        trellis.pixels.set(0, 0, 0, 255);
        trellis.pixels.show();
        sleep_ms(500);
    }
    return 0;
}

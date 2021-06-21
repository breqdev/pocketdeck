#include <stdio.h>
#include "pico/stdlib.h"
#include "main.h"
#include "i2c.h"


int main() {
    stdio_init_all();

    i2c_setup();

    while (true) {
        printf(MESSAGE);
        sleep_ms(1000);
    }
    return 0;
}

#include <stdio.h>
#include "pico/stdlib.h"
#include "main.h"

int main() {
    stdio_init_all();
    while (true) {
        printf(MESSAGE);
        sleep_ms(1000);
    }
    return 0;
}

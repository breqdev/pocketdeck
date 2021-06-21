#include "main.h"

#include "pico/binary_info.h"
#include "hardware/i2c.h"

#define FEATHER_I2C i2c1
#define FEATHER_SDA 2
#define FEATHER_SCL 3


void i2c_setup() {
    i2c_init(FEATHER_I2C, 100 * 1000);

    gpio_set_function(FEATHER_SDA, GPIO_FUNC_I2C);
    gpio_set_function(FEATHER_SCL, GPIO_FUNC_I2C);

    gpio_pull_up(FEATHER_SDA);
    gpio_pull_up(FEATHER_SCL);
}
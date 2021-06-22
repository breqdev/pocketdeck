#include "drivers/seesaw.h"


Seesaw::Seesaw(uint8_t address) : address(address) {};


uint8_t* Seesaw::add_header(uint8_t module_base, uint8_t module_function, uint8_t* data, size_t length) {
    size_t buflen = length + HEADER_LENGTH;
    uint8_t* buffer = new uint8_t[buflen];

    buffer[0] = module_base;
    buffer[1] = module_function;

    std::copy(data, data + length, buffer + HEADER_LENGTH);

    return buffer;
}

void Seesaw::write(uint8_t module_base, uint8_t module_function, uint8_t* data, size_t length) {
    uint8_t* buffer = add_header(module_base, module_function, data, length);

    i2c_write_blocking(
        FEATHER_I2C,
        address,
        buffer,
        length + HEADER_LENGTH,
        false
    );

    delete[] buffer;
}

void Seesaw::read(uint8_t module_base, uint8_t module_function, uint8_t* data, size_t length, uint16_t delay) {
    uint8_t header[] = {module_base, module_function};

    i2c_write_blocking(
        FEATHER_I2C,
        address,
        header,
        2,
        false
    );

    sleep_us(delay);

    i2c_read_blocking(
        FEATHER_I2C,
        address,
        data,
        length,
        false
    );
}
#include "drivers/keypad.h"

Keypad::Keypad(Seesaw& seesaw) : seesaw(seesaw) {};


void Keypad::init() {
    // Enable interrupts
    uint8_t interrupt_enable[] = {1};

    seesaw.write(
        MODULE_BASE,
        INTENSET,
        interrupt_enable,
        1
    );

    // Activate key events
    for (uint8_t i = 0; i < 16; ++i) {
        uint8_t key = key_trellis_to_seesaw(i);

        uint8_t activate_rising[] = {key, (1 << (RISING + 1)) | 1};

        seesaw.write(
            MODULE_BASE,
            EVENT,
            activate_rising,
            2
        );

        uint8_t activate_falling[] = {key, (1 << (FALLING + 1)) | 1};

        seesaw.write(
            MODULE_BASE,
            EVENT,
            activate_falling,
            2
        );
    }
}
uint8_t* Keypad::events(uint8_t& count) {
    // Get the number of incoming events
    seesaw.read(
        MODULE_BASE,
        COUNT,
        &count,
        1,
        500
    );

    if (count == 0) {
        return nullptr;
    }

    // Read in all the events
    uint8_t* events = new uint8_t[count];

    seesaw.read(
        MODULE_BASE,
        FIFO,
        events,
        count,
        1000
    );

    for (uint8_t i = 0; i < count; ++i) {
        uint8_t key = events[i] >> 2;
        key = key_seesaw_to_trellis(key);
        events[i] &= 0x03;
        events[i] |= (key << 2);
    }

    return events;
}

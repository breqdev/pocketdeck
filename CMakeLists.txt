cmake_minimum_required(VERSION 3.13)
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)


# initialize pico-sdk from submodule
# note: this must happen before project()
include(pico-sdk/pico_sdk_init.cmake)

project(pocketdeck)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# initialize lvgl
add_subdirectory(lvgl)

# rest of your project
add_subdirectory(src)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(main pico_stdlib hardware_i2c lvgl)

pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 0)

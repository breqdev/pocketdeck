cmake_minimum_required(VERSION 3.13)

# initialize pico-sdk from submodule
# note: this must happen before project()
include(pico-sdk/pico_sdk_init.cmake)

project(pocketdeck)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
include_directories(include)
add_subdirectory(src)

pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 0)

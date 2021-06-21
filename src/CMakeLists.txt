include(../pico-sdk/pico_sdk_init.cmake)

add_executable(
    main
    main.cpp
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(main pico_stdlib hardware_i2c)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(main)
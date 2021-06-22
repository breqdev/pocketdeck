include(../pico-sdk/pico_sdk_init.cmake)

file(GLOB SOURCES *.cpp)

add_executable(
    main
    ${SOURCES}
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(main pico_stdlib hardware_i2c)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(main)
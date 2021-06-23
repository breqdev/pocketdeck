include(../pico-sdk/pico_sdk_init.cmake)

include_directories(.. ../include)

file(GLOB SOURCES *.cpp)

add_executable(
    main
    ${SOURCES}
)

add_subdirectory(drivers)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(main)
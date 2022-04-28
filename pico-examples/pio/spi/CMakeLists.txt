cmake_minimum_required(VERSION 3.13)

# Pull in SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pio_spi_loopback C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# Initialize the SDK
pico_sdk_init()

add_executable(pio_spi_flash)

pico_generate_pio_header(pio_spi_flash ${CMAKE_CURRENT_LIST_DIR}/spi.pio)

target_sources(pio_spi_flash PRIVATE
        spi_flash.c
        pio_spi.c
        pio_spi.h
        )

target_link_libraries(pio_spi_flash PRIVATE pico_stdlib hardware_pio)
pico_add_extra_outputs(pio_spi_flash)

example_auto_set_url(pio_spi_flash)

add_executable(pio_spi_loopback)

pico_generate_pio_header(pio_spi_loopback ${CMAKE_CURRENT_LIST_DIR}/spi.pio)

target_sources(pio_spi_loopback PRIVATE
        spi_loopback.c
        pio_spi.c
        pio_spi.h
        )

target_link_libraries(pio_spi_loopback PRIVATE pico_stdlib hardware_pio)
pico_add_extra_outputs(pio_spi_loopback)
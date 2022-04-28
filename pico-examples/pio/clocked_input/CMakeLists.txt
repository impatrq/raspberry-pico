cmake_minimum_required(VERSION 3.13)

# Pull in SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pio_clocked_input C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# Initialize the SDK
pico_sdk_init()

add_executable(pio_clocked_input)

pico_generate_pio_header(pio_clocked_input ${CMAKE_CURRENT_LIST_DIR}/clocked_input.pio)

target_sources(pio_clocked_input PRIVATE clocked_input.c)

target_link_libraries(pio_clocked_input PRIVATE
        pico_stdlib
        hardware_pio
        hardware_spi
        )

pico_add_extra_outputs(pio_clocked_input)
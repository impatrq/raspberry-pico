cmake_minimum_required(VERSION 3.13)

# Pull in SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pio_logic_analyser C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# Initialize the SDK
pico_sdk_init()

add_executable(pio_logic_analyser)

target_sources(pio_logic_analyser PRIVATE logic_analyser.c)

target_link_libraries(pio_logic_analyser PRIVATE pico_stdlib hardware_pio hardware_dma)
pico_add_extra_outputs(pio_logic_analyser)
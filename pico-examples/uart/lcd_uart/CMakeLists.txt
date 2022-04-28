cmake_minimum_required(VERSION 3.13)

# Pull in SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(lcd_uart C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# Initialize the SDK
pico_sdk_init()

add_executable(lcd_uart
        lcd_uart.c
        )

# pull in common dependencies and additional uart hardware support
target_link_libraries(lcd_uart pico_stdlib hardware_uart)

# enable usb output and uart output
# modify here as required
pico_enable_stdio_usb(lcd_uart 1)
pico_enable_stdio_uart(lcd_uart 1)

# create map/bin/hex file etc.
pico_add_extra_outputs(lcd_uart)
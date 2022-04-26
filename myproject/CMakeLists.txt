cmake_minimum_required(VERSION 3.13)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

# Change myproject_test for directory name
project(hello_usb C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# Initialize the SDK
pico_sdk_init()

if (TARGET tinyusb_device)
    add_executable(usb
            main.c
            )

    # pull in common dependencies
    target_link_libraries(usb pico_stdlib)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(usb 1)
    pico_enable_stdio_uart(usb 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(usb)

elseif(PICO_ON_DEVICE)
    message(WARNING "not building hello_usb because TinyUSB submodule is not initialized in the SDK")
endif()

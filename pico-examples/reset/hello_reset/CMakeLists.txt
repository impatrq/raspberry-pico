cmake_minimum_required(VERSION 3.13)

# Pull in SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(hello_reset C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# Initialize the SDK
pico_sdk_init()

if (TARGET hardware_resets)
    add_executable(hello_reset
            hello_reset.c
            )

    # pull in common dependencies and additional reset hardware support
    target_link_libraries(hello_reset pico_stdlib hardware_resets)

    # create map/bin/hex file etc.
    pico_add_extra_outputs(hello_reset)

endif ()

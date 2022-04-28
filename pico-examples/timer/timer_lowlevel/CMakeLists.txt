cmake_minimum_required(VERSION 3.13)

# Pull in SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(timer_lowlevel C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# Initialize the SDK
pico_sdk_init()

if (PICO_ON_DEVICE)
    add_executable(timer_lowlevel
            timer_lowlevel.c)

    # Disable SDK alarm support for this lowlevel example
    set(PICO_TIME_DEFAULT_ALARM_POOL_DISABLED 1)

    target_link_libraries(timer_lowlevel pico_stdlib)

    # create map/bin/hex file etc.
    pico_add_extra_outputs(timer_lowlevel)

endif ()
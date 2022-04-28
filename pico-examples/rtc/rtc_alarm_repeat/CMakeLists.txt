cmake_minimum_required(VERSION 3.13)

# Pull in SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(rtc_alarm_repeat C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# Initialize the SDK
pico_sdk_init()

add_executable(rtc_alarm_repeat
        rtc_alarm_repeat.c
        )

# pull in common dependencies and additional rtc hardware support
target_link_libraries(rtc_alarm_repeat pico_stdlib hardware_rtc)

# create map/bin/hex file etc.
pico_add_extra_outputs(rtc_alarm_repeat)
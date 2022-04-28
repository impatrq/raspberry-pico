cmake_minimum_required(VERSION 3.13)

# Pull in SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pio_squarewave C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# Initialize the SDK
pico_sdk_init()

add_executable(pio_squarewave)

pico_generate_pio_header(pio_squarewave ${CMAKE_CURRENT_LIST_DIR}/squarewave.pio)
pico_generate_pio_header(pio_squarewave ${CMAKE_CURRENT_LIST_DIR}/squarewave_wrap.pio)
pico_generate_pio_header(pio_squarewave ${CMAKE_CURRENT_LIST_DIR}/squarewave_fast.pio)

target_sources(pio_squarewave PRIVATE squarewave.c)

target_link_libraries(pio_squarewave PRIVATE pico_stdlib hardware_pio)
pico_add_extra_outputs(pio_squarewave)

# generate .hex file and .pio.h file for the RP2040 datasheet (to make sure
# the datasheet always shows the output of the latest pioasm version)
add_custom_target(pio_squarewave_datasheet DEPENDS
		${CMAKE_CURRENT_LIST_DIR}/generated/squarewave.hex
		${CMAKE_CURRENT_LIST_DIR}/generated/squarewave.pio.h
		${CMAKE_CURRENT_LIST_DIR}/generated/squarewave_wrap.pio.h
		)
add_custom_command(OUTPUT ${CMAKE_CURRENT_LIST_DIR}/generated/squarewave.hex
        DEPENDS ${CMAKE_CURRENT_LIST_DIR}/squarewave.pio
        COMMAND Pioasm -o hex ${CMAKE_CURRENT_LIST_DIR}/squarewave.pio ${CMAKE_CURRENT_LIST_DIR}/generated/squarewave.hex
        )
add_custom_command(OUTPUT ${CMAKE_CURRENT_LIST_DIR}/generated/squarewave.pio.h
        DEPENDS ${CMAKE_CURRENT_LIST_DIR}/squarewave.pio
        COMMAND Pioasm ${CMAKE_CURRENT_LIST_DIR}/squarewave.pio ${CMAKE_CURRENT_LIST_DIR}/generated/squarewave.pio.h
        )
add_custom_command(OUTPUT ${CMAKE_CURRENT_LIST_DIR}/generated/squarewave_wrap.pio.h
        DEPENDS ${CMAKE_CURRENT_LIST_DIR}/squarewave_wrap.pio
        COMMAND Pioasm ${CMAKE_CURRENT_LIST_DIR}/squarewave_wrap.pio ${CMAKE_CURRENT_LIST_DIR}/generated/squarewave_wrap.pio.h
        )
add_dependencies(pio_squarewave pio_squarewave_datasheet)

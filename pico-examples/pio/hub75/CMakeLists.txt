cmake_minimum_required(VERSION 3.13)

# Pull in SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pio_hub75 C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# Initialize the SDK
pico_sdk_init()

add_executable(pio_hub75)

pico_generate_pio_header(pio_hub75 ${CMAKE_CURRENT_LIST_DIR}/hub75.pio)

target_sources(pio_hub75 PRIVATE hub75.c)

target_compile_definitions(pio_hub75 PRIVATE
	PICO_DEFAULT_UART_TX_PIN=28
	PICO_DEFAULT_UART_RX_PIN=29
)

target_link_libraries(pio_hub75 PRIVATE pico_stdlib hardware_pio)
pico_add_extra_outputs(pio_hub75)
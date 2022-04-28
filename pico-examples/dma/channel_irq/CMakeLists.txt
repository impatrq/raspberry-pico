cmake_minimum_required(VERSION 3.13)

# Pull in SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(dma_channel_irq C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# Initialize the SDK
pico_sdk_init()

add_executable(dma_channel_irq
        channel_irq.c
        )

pico_generate_pio_header(dma_channel_irq ${CMAKE_CURRENT_LIST_DIR}/pio_serialiser.pio)

target_link_libraries(
	dma_channel_irq
	pico_stdlib
        hardware_dma
        hardware_irq
        hardware_pio
)

# create map/bin/hex file etc.
pico_add_extra_outputs(dma_channel_irq)
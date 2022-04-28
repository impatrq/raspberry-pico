cmake_minimum_required(VERSION 3.13)

# Pull in SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(adc_dma_capture C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# Initialize the SDK
pico_sdk_init()

add_executable(adc_dma_capture
        dma_capture.c
        )

pico_generate_pio_header(adc_dma_capture ${CMAKE_CURRENT_LIST_DIR}/resistor_dac.pio)

target_link_libraries(adc_dma_capture
		pico_stdlib
		hardware_adc
		hardware_dma
		# For the dummy output:
		hardware_pio
		pico_multicore
		)

# create map/bin/hex file etc.
pico_add_extra_outputs(adc_dma_capture)
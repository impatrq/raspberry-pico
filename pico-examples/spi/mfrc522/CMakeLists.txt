# Set CMake minimum version
cmake_minimum_required(VERSION 3.13)

# Pull in SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Change project_name with the current project name (sets PROJECT_NAME variable)
project(main C CXX ASM)

# Set C/CPP standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Set library root directory
set(LIBS lib)

# SDK versino error message
if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# Initialize the Pico SDK
pico_sdk_init()

# Add libraries (remove comment to add)
add_library(mfrc
	# Add libraries with ${LIBS}/FILENAME.c
    ${LIBS}/mfrc522.c
)

# Include header files to library (remove commenta to add headers)
target_include_directories(mfrc PUBLIC 
    ${LIBS}/inc
)

# Link libraries with SDK (remove comments to link libraries)
target_link_libraries(mfrc 
	# Add library name to link
    pico_stdlib
    hardware_spi
)

# Add the source files
add_executable(${PROJECT_NAME}
	main.c
)

# Enable/disable stdio output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

# Link libraries with main project
target_link_libraries(${PROJECT_NAME} 
    pico_stdlib
    # Remove next comment if libraries where added to the libs directory
    mfrc
    # Add other libraries used in the main file
)

# create map/bin/hex file etc.
pico_add_extra_outputs(${PROJECT_NAME})
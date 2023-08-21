cmake_minimum_required(VERSION 3.10)

project(
    NTTGameEngineProject
    VERSION 1.0.0
)

option(COMPILE_VISION_EXAMPLE "Compile Vision Example" OFF)
option(COMPILE_UART_EXAMPLE "Compile UART Example" OFF)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/NTTEngine)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/GameExample)

if (COMPILE_VISION_EXAMPLE)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/VisionProject)
endif()

if (COMPILE_UART_EXAMPLE)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/UARTProject)
endif()
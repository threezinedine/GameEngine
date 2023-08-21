project(
    UART
)

file(
    GLOB
    UART_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(
    ${PROJECT_NAME}
    STATIC
    ${UART_SRC_FILES}
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    NTTEngineLog
    NTTEngineThreadSystem
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

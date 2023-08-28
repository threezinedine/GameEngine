project(
    SerialFrame
)

file(
    GLOB
    SERIAL_FRAME_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(
    ${PROJECT_NAME}
    STATIC
    ${SERIAL_FRAME_SRC_FILES}
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    NTTEngine
)
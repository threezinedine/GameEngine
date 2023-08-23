cmake_minimum_required(VERSION 3.10)

project(
    VisionApplication
)

file(
    GLOB
    SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/components)


add_executable(
    ${PROJECT_NAME}
    ${SRC_FILES}
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    ${OpenCV_LIBS}
    MQTT
    ImageProcessing
    NTTEngine
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${OpenCV_INCLUDE_DIRS}
)
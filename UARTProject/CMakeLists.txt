project(
    UARTCom
)

file(
    GLOB
    SRC_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/components)

add_executable(
    ${PROJECT_NAME}
    ${SRC_FILES}
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    NTTEngine
    UART
)
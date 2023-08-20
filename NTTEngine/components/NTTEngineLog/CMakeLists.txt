project(
    NTTEngineLog
)

file(
    GLOB
    LOGGING_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor)

add_library(
    ${PROJECT_NAME}
    STATIC
    ${LOGGING_SRC_FILES}
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    spdlog
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
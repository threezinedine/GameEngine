project(
    NTTEngineProfiling
)

file(
    GLOB
    PROFILING_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(
    ${PROJECT_NAME}
    STATIC
    ${PROFILING_SRC_FILES}
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    NTTEngineLog
)
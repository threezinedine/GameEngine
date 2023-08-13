project(
    ConfigurationCppLibs
    VERSION 1.0.0
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)

file(
    GLOB
    LIBRARY_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(
    ${PROJECT_NAME}
    STATIC
    ${LIBRARY_SRC_FILES}
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    nlohmann_json
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/json/include
)
project(
    SimpleExample
)

file(
    GLOB
    EXAMPLE_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_executable(
    ${PROJECT_NAME}
    ${EXAMPLE_SRC_FILES}
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    ConfigurationCppLibs
)
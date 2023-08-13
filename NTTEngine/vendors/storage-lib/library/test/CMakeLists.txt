project(
    LibTest
    VERSION 1.0.0
)

file(
    GLOB
    TEST_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_executable(
    ${PROJECT_NAME}
    ${TEST_SRC_FILES}
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    gtest
    gmock
    ConfigurationCppLibs
)
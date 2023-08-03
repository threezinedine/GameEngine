project(
    NTTEngine
)

# listing all src files
file(
    GLOB
    SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

# define that this is engine code -> not create the main function
add_definitions(-DNTT_ENGINE_BUILD)


add_library(
    ${PROJECT_NAME}
    SHARED
    ${SRC_FILES}
)


target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
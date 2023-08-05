project(
    NTTEngine
)

# listing all src files
file(
    GLOB
    SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)


# find opengl
find_package(OpenGL REQUIRED)

# define that this is engine code -> not create the main function
add_definitions(-DNTT_ENGINE_BUILD)

# add library 
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs)

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


target_link_libraries(
    ${PROJECT_NAME}
    spdlog
    OpenGL::GL
    libglew_static
    glfw
)
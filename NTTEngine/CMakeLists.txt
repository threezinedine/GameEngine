project(
    NTTEngine
)

# listing all src files
file(
    GLOB
    SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

option(OPENGL_PLATFORM "OpenGL plaform" ON)
option(WINDOWS_OS "Windows OS" ON)

# find opencv lib
option(OPENCV_LIB_PATH "The folder which contain the opencv package")
find_package(OpenCV REQUIRED PATHS ${OPENCV_LIB_PATH})

# find opengl
find_package(OpenGL REQUIRED)

# define that this is engine code -> not create the main function
add_definitions(-DNTT_ENGINE_BUILD)

# add library 
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendors)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/components)

add_library(
    ${PROJECT_NAME}
    STATIC
    ${SRC_FILES}
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${OpenCV_INCLUDE_DIRS}
)


target_link_libraries(
    ${PROJECT_NAME}
    NTTEngineLog
    NTTEngineCore
    NTTEngineEventSystem
    NTTEngineRenderer
    NTTEngineWindow
    NTTEngineLayerSystem
    ImGui
    OpenGL::GL
    libglew_static
    glfw
    glm
    ConfigurationCppLibs
    ${OpenCV_LIBS}
)
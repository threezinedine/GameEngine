project(
    NTTEngineImGuiTools
)

option(OPENGL_PLATFORM "OpenGL plaform" ON)

file(
    GLOB
    IMGUI_TOOLS_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

set(
    IMGUI_TOOLS_INCLUDE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

file(
    GLOB
    OPENGL_IMGUI_TOOLS_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/Platforms/OpenGL/src/*.cpp
)

set(
    OPENGL_IMGUI_TOOLS_INCLUDE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/Platforms/OpenGL/include
)

if (OPENGL_PLATFORM)
    set(
        INCLUDE_DIRS 
        ${IMGUI_TOOLS_INCLUDE_PATH}
        ${OPENGL_IMGUI_TOOLS_INCLUDE_PATH}
    )
    set(
        SRC_FILES
        ${IMGUI_TOOLS_SRC_FILES}
        ${OPENGL_IMGUI_TOOLS_SRC_FILES}
    )
    add_definitions(-DOPENGL_PLATFORM)
endif()

add_library(
    ${PROJECT_NAME}
    STATIC
    ${SRC_FILES}
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    NTTEngineLog
    # NTTEngineCore
    # NTTEngineUtils
    # NTTEngineEventSystem
    # ConfigurationCppLibs
    libglew_static
    glfw
    # glm
    ImGui
    ${OpenCV_LIBS}
)
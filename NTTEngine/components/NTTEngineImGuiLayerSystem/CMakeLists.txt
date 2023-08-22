project(
    NTTEngineImGuiLayerSystem
)

file(
    GLOB
    IMGUI_LAYER_SYSTEM_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

file(
    GLOB
    OPENGL_IMGUI_LAYER_SYSTEM_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/Platforms/OpenGL/src/*.cpp
)

message("${OPENGL_IMGUI_LAYER_SYSTEM_SRC_FILES}")

set(
    IMGUI_LAYER_SYSTEM_INCLUDE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(
    OPENGL_IMGUI_LAYER_SYSTEM_INCLUDE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/Platforms/OpenGL/include
)

if (OPENGL_PLATFORM)
    set(
        SRC_FILES
        ${IMGUI_LAYER_SYSTEM_SRC_FILES}
        ${OPENGL_IMGUI_LAYER_SYSTEM_SRC_FILES}
    )
    set(
        INCLUDE_PATHS
        ${IMGUI_LAYER_SYSTEM_INCLUDE_PATH}
        ${OPENGL_IMGUI_LAYER_SYSTEM_INCLUDE_PATH}
    )
else()
    set(
        SRC_FILES
        ${IMGUI_LAYER_SYSTEM_SRC_FILES}
    )
    set(
        INCLUDE_PATHS
        ${IMGUI_LAYER_SYSTEM_INCLUDE_PATH}
    )
endif()

add_library(
    ${PROJECT_NAME}
    STATIC
    ${SRC_FILES}
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    ImGui
    NTTEngineLog
    NTTEngineLayerSystem
    NTTEngineThreadSystem
    libglew_static
    glfw
    NTTEngineWindow
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${INCLUDE_PATHS}
)
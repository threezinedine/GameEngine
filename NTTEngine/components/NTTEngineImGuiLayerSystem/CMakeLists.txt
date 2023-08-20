project(
    NTTEngineImGuiLayerSystem
)

file(
    GLOB
    IMGUI_LAYER_SYSTEM_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(
    ${PROJECT_NAME}
    STATIC
    ${IMGUI_LAYER_SYSTEM_SRC_FILES}
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    ImGui
    NTTEngineLog
    NTTEngineLayerSystem
    libglew_static
    glfw
    NTTEngineWindow
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
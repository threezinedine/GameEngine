project(
    ImGui
)

file(
    GLOB
    IMGUI_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
)

add_library(
    ${PROJECT_NAME}
    ${IMGUI_SRC_FILES}
)


target_link_libraries(
    ${PROJECT_NAME}
    glfw
)


target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/backends
)
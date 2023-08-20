project(
    NTTEngineWindow
)

file(
    GLOB
    WINDOW_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

set(
    WINDOW_INCLUDE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

file(
    GLOB
    WINDOWS_WINDOW_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/Platforms/windows/src/*.cpp
)

set(
    WINDOWS_WINDOW_INCLUDE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/Platforms/windows/include
)

if (WINDOWS_OS)
    set(
        INCLUDE_DIRS 
        ${WINDOW_INCLUDE_PATH}
        ${WINDOWS_WINDOW_INCLUDE_PATH}
    )
    set(
        SRC_FILES
        ${WINDOW_SRC_FILES}
        ${WINDOWS_WINDOW_SRC_FILES}
    )
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
    NTTEngineEventSystem
    NTTEngineRenderer
    ConfigurationCppLibs
    libglew_static
    glfw
    ${OpenCV_LIBS}
)
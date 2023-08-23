project(
    ImageProcessing
)

file(
    GLOB
    IMAGE_PROCESSING_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(
    ${PROJECT_NAME}
    STATIC
    ${IMAGE_PROCESSING_SRC_FILES}
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    NTTEngineThreadSystem
    NTTEngineImGuiLayerSystem
    NTTEngineImGuiTools
    ${OpenCV_LIBS}
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${OpenCV_INCLUDE_DIRS}
)
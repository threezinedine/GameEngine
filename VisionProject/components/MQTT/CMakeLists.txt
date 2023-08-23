project(
    MQTT
)

set(MQTT_PAHO_CPP_PATH C:/mqtt/paho-cpp)
set(MQTT_PAHO_C_PATH C:/mqtt/paho-c)
set(PAHO_MQTT_C_LIBRARIES C:/mqtt/paho-c/lib/libpaho-mqtt3c-static.a)
set(PAHO_MQTT_C_INCLUDE_DIRS C:/mqtt/paho-c/include)

file(
    GLOB
    MQTT_C_LIBS
    ${MQTT_PAHO_C_PATH}/lib/*.a
)

file(
    GLOB
    MQTT_CPP_LIBS
    ${MQTT_PAHO_CPP_PATH}/lib/*.a
)

find_package(PahoMqttCpp REQUIRED PATHS ${MQTT_PAHO_CPP_PATH})

message("MQTT c libs: ${MQTT_C_LIBS}")
message("MQTT cpp libs: ${MQTT_CPP_LIBS}")

file(
    GLOB
    MQTT_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(
    ${PROJECT_NAME}
    STATIC
    ${MQTT_SRC_FILES}
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    ${MQTT_C_LIBS}
    ${MQTT_CPP_LIBS}
    PahoMqttCpp::paho-mqttpp3-static
    rpcrt4
    ws2_32
    Crypt32
    NTTEngineLog
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
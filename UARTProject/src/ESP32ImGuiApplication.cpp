#include "UART/UART.hpp"
#include "ESP32ImGuiApplication.hpp"


ESP32ImGuiApplication::ESP32ImGuiApplication()
    : ImGuiApplication("CommunicationForESP32")
{
    
}

ESP32ImGuiApplication::~ESP32ImGuiApplication()
{
    
}

void ESP32ImGuiApplication::OnImGuiRenderImpl(ntt::Timestep ts)
{
    UARTCom::OnImGuiRenderSta();

    if (ImGui::Button("Connect To Wifi"))
    {
        UARTCom::SubmitCommand(
            std::make_shared<UARTChangeCoilCommand>(0x00, true)
        );
    }

    if (ImGui::Button("Connect to MQTT Broker"))
    {
        UARTCom::SubmitCommand(
            std::make_shared<UARTChangeCoilCommand>(0x01, true)
        );
    }
}
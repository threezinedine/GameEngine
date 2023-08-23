#include "UART/UART.hpp"
#include "NTTEngineLog/NTTEngineLog.hpp"
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

    ImGui::Separator();
    static char ssid[20] = "";
    static char password[20] = "";

    ImGui::InputText("SSID", ssid, 32);
    ImGui::SameLine();
    if (ImGui::Button("Upload SSID"))
    {
        UARTCom::SubmitCommand(
            std::make_shared<UARTSendStringCommand>(0x09, std::string(ssid))
        );
    }
    ImGui::InputText("Password", password, 32);
    ImGui::SameLine();
    if (ImGui::Button("Upload Password"))
    {
        UARTCom::SubmitCommand(
            std::make_shared<UARTSendStringCommand>(0x0a, std::string(password))
        );
    }

    if (ImGui::Button("Connect To Wifi"))
    {
        UARTCom::SubmitCommand(
            std::make_shared<UARTChangeCoilCommand>(0x00, true)
        );
    }
    ImGui::SameLine();
    if (ImGui::Button("Disconnect Wifi"))
    {
        UARTCom::SubmitCommand(
            std::make_shared<UARTChangeCoilCommand>(0x00, false)
        );
    }

    ImGui::Separator();
    if (ImGui::Button("Connect to MQTT Broker"))
    {
        UARTCom::SubmitCommand(
            std::make_shared<UARTChangeCoilCommand>(0x01, true)
        );
    }
    ImGui::Separator();
}
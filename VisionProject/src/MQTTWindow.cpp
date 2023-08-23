#include <MQTTWindow.hpp>
#include <MQTT/MQTT.hpp>
#include <imgui.h>


float MQTTWindow::temperatureValue = 0.0f;

MQTTWindow::MQTTWindow()
    : ntt::ImGuiApplication("MQTT window")
{

}

MQTTWindow::~MQTTWindow()
{

}

void MQTTWindow::OnImGuiRenderImpl(ntt::Timestep ts)
{
    ImGui::SliderFloat("temperature", &MQTTWindow::temperatureValue, 0, 100);

    if (ImGui::Button("Send Temperature"))
    {
        MQTTClient::GetInstance()->Publish("temperature", std::to_string(MQTTWindow::temperatureValue)); 
    }
}
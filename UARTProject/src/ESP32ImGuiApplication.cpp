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
}
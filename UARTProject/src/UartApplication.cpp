#include "UartApplication.hpp"
#include "UartImGuiApplication.hpp"
#include "ESP32ImGuiApplication.hpp"


UartApplication::UartApplication()
    : ntt::Application(600, 800, std::string("UART Application"))
{
    UARTCom::Initialize();
}

UartApplication::~UartApplication()
{
    UARTCom::Release();
}

void UartApplication::OnSetupImpl()
{
    std::shared_ptr<ntt::ImGuiLayer> imguiLayer = std::make_shared<ntt::ImGuiLayer>("Debug Layer");

    imguiLayer->AddApplication(std::make_shared<ntt::WindowDemoApplication>());
    imguiLayer->AddApplication(std::make_shared<ntt::PerformanceApplication>(1));
    imguiLayer->AddApplication(std::make_shared<UartImGuiApplication>());

    layerStack_.PushOverlayLayer(imguiLayer);
    UARTCom::StartThread();
}

void UartApplication::OnUpdateImpl(ntt::Timestep ts)
{

}

void UartApplication::OnWindowCloseImpl(ntt::WindowCloseEvent& event)
{
    UARTCom::StopThread();
}
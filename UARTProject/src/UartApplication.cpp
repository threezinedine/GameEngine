#include "UartApplication.hpp"
#include "UartImGuiApplication.hpp"


UartApplication::UartApplication()
    : ntt::Application(600, 800, std::string("UART Application")),
        com_("COM7")
{

}

UartApplication::~UartApplication()
{
}

void UartApplication::OnSetupImpl()
{
    std::shared_ptr<ntt::ImGuiLayer> imguiLayer = std::make_shared<ntt::ImGuiLayer>("Debug Layer");

    imguiLayer->AddApplication(std::make_shared<ntt::WindowDemoApplication>());
    imguiLayer->AddApplication(std::make_shared<ntt::PerformanceApplication>(1));
    imguiLayer->AddApplication(std::make_shared<UartImGuiApplication>(com_));

    layerStack_.PushOverlayLayer(imguiLayer);
    com_.OnRun();
}

void UartApplication::OnUpdateImpl(ntt::Timestep ts)
{

}

void UartApplication::OnWindowCloseImpl(ntt::WindowCloseEvent& event)
{
    com_.Stop();
}
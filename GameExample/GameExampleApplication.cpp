#include "GameExampleApplication.hpp"
#include <NTTEngine/NTTEngine.hpp>
#include "TestLayer.hpp"
#include "TestWindow.hpp"


void GameExampleApplication::OnSetupImpl()
{
    auto imguiLayer = new ntt::ImGuiLayer("Debug Layer");
    imguiLayer->AddApplication(new ntt::WindowDemoApplication(), false);
    imguiLayer->AddApplication(new TestWindow(std::string("Test window")));

    layerStack_.PushLayer(new TestLayer());
    layerStack_.PushOverlayLayer(imguiLayer);
    ntt::WindowInput::Initialzie();

}

void GameExampleApplication::OnUpdateImpl()
{

}
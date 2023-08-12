#include "GameExampleApplication.hpp"
#include <NTTEngine/NTTEngine.hpp>
#include "TestLayer.hpp"
#include "TestWindow.hpp"
#include "TestSliderComponent.hpp"


void GameExampleApplication::OnSetupImpl()
{
    auto testLayer = new TestLayer();
    auto imguiLayer = new ntt::ImGuiLayer("Debug Layer");

    auto testWindow = new TestWindow(std::string("Test window"));
    testWindow->AddComponent(new TestSliderComponent());
    testWindow->AddComponent(testLayer);

    imguiLayer->AddApplication(new ntt::WindowDemoApplication(), false);
    imguiLayer->AddApplication(testWindow);

    layerStack_.PushLayer(testLayer);
    layerStack_.PushOverlayLayer(imguiLayer);
    ntt::WindowInput::Initialzie();

}

void GameExampleApplication::OnUpdateImpl()
{

}
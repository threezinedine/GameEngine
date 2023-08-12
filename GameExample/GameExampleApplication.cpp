#include "GameExampleApplication.hpp"
#include <NTTEngine/NTTEngine.hpp>
#include "TestLayer.hpp"
#include "TestWindow.hpp"
#include "TestSliderComponent.hpp"


void GameExampleApplication::OnSetupImpl()
{
    auto testLayer = std::make_shared<TestLayer>();
    auto imguiLayer = std::make_shared<ntt::ImGuiLayer>("Debug Layer");

    auto testWindow = std::make_shared<TestWindow>(std::string("Test window"));
    testWindow->AddComponent(std::make_shared<TestSliderComponent>());
    testWindow->AddComponent(testLayer);

    imguiLayer->AddApplication(std::make_shared<ntt::WindowDemoApplication>(), false);
    imguiLayer->AddApplication(testWindow);

    layerStack_.PushLayer(testLayer);
    layerStack_.PushOverlayLayer(imguiLayer);
    ntt::WindowInput::Initialzie();

}

void GameExampleApplication::OnUpdateImpl()
{

}
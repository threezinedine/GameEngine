#include "GameExampleApplication.hpp"
#include <NTTEngine/NTTEngine.hpp>
#include "TestLayer.hpp"
#include "TestWindow.hpp"
#include "TestSliderComponent.hpp"
#include "Renderer2DLayer.hpp"


void GameExampleApplication::OnSetupImpl()
{
    // auto testLayer = std::make_shared<TestLayer>(defaultCamera_);
    auto renderer2DLayer = std::make_shared<Renderer2DLayer>(defaultCamera_);
    auto imguiLayer = std::make_shared<ntt::ImGuiLayer>("Debug Layer");

    auto testWindow = std::make_shared<TestWindow>(std::string("Test window"));
    // testWindow->AddComponent(testLayer);
    testWindow->AddComponent(renderer2DLayer);

    imguiLayer->AddApplication(std::make_shared<ntt::WindowDemoApplication>());
    imguiLayer->AddApplication(testWindow);
    imguiLayer->AddApplication(std::make_shared<ntt::PerformanceApplication>());

    // layerStack_.PushLayer(testLayer);
    layerStack_.PushLayer(renderer2DLayer);
    layerStack_.PushOverlayLayer(imguiLayer);

    // window_->SetVSync(true);
}

void GameExampleApplication::OnUpdateImpl(ntt::Timestep ts)
{

}
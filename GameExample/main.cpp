#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <glm/vec3.hpp>

#include <NTTEngine/NTTEngine.hpp>

class TestWindow: public ntt::ImGuiApplication
{
    public:
        TestWindow(std::string windowName)
            : ImGuiApplication(windowName) {}
        void OnImGuiRenderImpl() override 
        {
            ImGui::Text("Home");
        }
};

class TestLayer: public ntt::Layer
{
    public:
        TestLayer(): Layer("Test Layer") {}
};

class GameExampleApplication: public ntt::Application
{
    public:
        GameExampleApplication()
            : Application(600, 800, "Example")
        {

        } 

        ~GameExampleApplication()
        {

        }

        void OnSetupImpl() override
        {
            auto imguiLayer = new ImGuiLayer("Debug Layer");
            imguiLayer->AddApplication(new WindowDemoApplication());
            imguiLayer->AddApplication(new TestWindow(std::string("Test window")));

            layerStack_.PushLayer(new TestLayer());
            layerStack_.PushOverlayLayer(imguiLayer);
            WindowInput::Initialzie();
        }
    private:
};


ntt::Application* CreateApplication()
{
    return new GameExampleApplication();
}
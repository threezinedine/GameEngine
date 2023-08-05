#include <iostream>
#include <string>
#include <memory>
#include <sstream>

#include <NTTEngine/NTTEngine.hpp>

class TestLayer: public ntt::Layer
{
    public:
        TestLayer(): Layer("Test Layer") {}

        void OnMouseMove(MouseMoveEvent& event) override
        {
            NTT_APPLICATION_INFO("Mouse move from test layer: (" + std::to_string(event.GetMouseX())
                                    + ", " + std::to_string(event.GetMouseY()) + ")");
        }
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
            layerStack_.PushLayer(new TestLayer());
            layerStack_.PushOverlayLayer(new ImGuiLayer("Debug Layer"));
            WindowInput::Initialzie();
        }

        void OnUpdateImpl() override
        {
            if (WindowInput::IsButtonLeftClicked())
            {
                NTT_APPLICATION_INFO("Left Button clicked");
            }
        }
    private:
};


ntt::Application* CreateApplication()
{
    return new GameExampleApplication();
}
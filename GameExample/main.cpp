#include <iostream>
#include <memory>
#include <sstream>

#include <NTTEngine/NTTEngine.hpp>

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

        void OnWindowCloseImpl(WindowCloseEvent& event) override
        {
            NTT_APPLICATION_INFO("Close the window");
        }

        void OnSetupImpl() override
        {
            layerStack_.PushLayer(new TestLayer());
        }

        void OnUpdateImpl() override
        {

        }

        void OnKeyReleaseImpl(KeyReleaseEvent& event) override
        {
            NTT_APPLICATION_DEBUG("Key release from application."); 
        }
    private:
};


ntt::Application* CreateApplication()
{
    return new GameExampleApplication();
}
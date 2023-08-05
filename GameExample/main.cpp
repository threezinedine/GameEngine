#include <iostream>
#include <memory>
#include <sstream>

#include <NTTEngine/NTTEngine.hpp>

class TestLayer: public ntt::Layer
{
    public:
        TestLayer(): Layer("Test Layer") {}

        void OnKeyRelease(KeyReleaseEvent& event) override
        {
            NTT_APPLICATION_INFO("Key release from test layer");
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

        void OnWindowCloseImpl(WindowCloseEvent& event) override
        {
            NTT_APPLICATION_INFO("Close the window");
        }

        void OnSetup() override
        {
            layerStack_.PushLayer(new TestLayer());
            NTT_APPLICATION_DEBUG("layerStack_ size: " + std::to_string(layerStack_.GetSize()));
        }

        void OnUpdate() override
        {
            while(!window_->IsClosed())
            {
                window_->OnUpdate();
            }
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
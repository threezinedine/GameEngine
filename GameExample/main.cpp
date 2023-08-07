#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <glm/vec3.hpp>

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

        void OnSetupImpl() override
        {
            layerStack_.PushLayer(new TestLayer());
            layerStack_.PushOverlayLayer(new ImGuiLayer("Debug Layer"));
            WindowInput::Initialzie();
            glm::vec3 pos(1.0f, 1.0f, 1.0f);
            glm::vec3 pos2(1.0f, 2.0f, 1.0f);
            glm::vec3 res = pos * pos2.t;
            std::cout << res.x << std::endl;
            std::cout << res.y << std::endl;
            std::cout << res.z << std::endl;
        }
    private:
};


ntt::Application* CreateApplication()
{
    return new GameExampleApplication();
}
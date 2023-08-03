#include <iostream>
#include <memory>

#include <NTTEngine/NTTEngine.hpp>

class GameExampleApplication: public ntt::Application
{
    public:
        GameExampleApplication()
        {

        } 

        ~GameExampleApplication()
        {

        }

        void Run() override
        {
            NTT_APPLICATION_INFO("Initialize the GLEW");
            std::cout << "Run From Here" << std::endl;
        }
};


ntt::Application* CreateApplication()
{
    return new GameExampleApplication();
}
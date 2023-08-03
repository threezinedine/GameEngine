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
            std::cout << "Run From Here" << std::endl;
        }
};


ntt::Application* CreateApplication()
{
    return new GameExampleApplication();
}
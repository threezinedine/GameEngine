#include <iostream>
#include <memory>
#include <sstream>

#include <NTTEngine/NTTEngine.hpp>

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

        void OnWindowClose(Event& event) override
        {
            NTT_APPLICATION_INFO("Close the window");
        }

        void Setup() override
        {

        }

        void Run() override
        {
            while(!window_->IsClosed())
            {
                window_->OnUpdate();
            }
        }
    private:
};


ntt::Application* CreateApplication()
{
    return new GameExampleApplication();
}
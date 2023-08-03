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
            delete window_;
        }

        void OnGameEnd(Event& event)
        {
            ntt::GameEndEvent& gameEndEvent = dynamic_cast<ntt::GameEndEvent&>(event);
            NTT_APPLICATION_INFO(gameEndEvent.GetMessage());
        }

        void Setup() override
        {
            window_ = new WinWindow(600, 800, "Example");
            window_->AddEvent(
                ON_GAME_END, 
                std::bind(&GameExampleApplication::OnGameEnd, this, std::placeholders::_1)
            );
        }

        void Run() override
        {
            while(!window_->IsClosed())
            {
                window_->OnUpdate();
            }
        }

    private:
        ntt::EventDispatcher dispatcher_;
        IWindow* window_ = nullptr;
};


ntt::Application* CreateApplication()
{
    return new GameExampleApplication();
}
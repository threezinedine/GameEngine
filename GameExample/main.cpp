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

        void OnGameEnd(Event& event)
        {
            ntt::GameEndEvent& gameEndEvent = dynamic_cast<ntt::GameEndEvent&>(event);
            NTT_APPLICATION_INFO(gameEndEvent.GetMessage());
        }

        void Setup() override
        {
            dispatcher_.AddEvent(ON_GAME_END, 
                    std::bind(&GameExampleApplication::OnGameEnd, this, std::placeholders::_1));
        }

        void Run() override
        {
            NTT_APPLICATION_INFO("Initialize the GLEW");
            std::cout << "Run From Here" << std::endl;

            std::string message = "End of Game";
            ntt::GameEndEvent event(message);
            dispatcher_.Dispatch(event);
        }

    private:
        ntt::EventDispatcher dispatcher_;
};


ntt::Application* CreateApplication()
{
    return new GameExampleApplication();
}
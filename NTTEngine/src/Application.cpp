#include <iostream>

#include <NTTEngine/Application.hpp>
#include <NTTEngine/Platforms/Platforms.hpp>


namespace ntt
{
    #define BIND_FUNCTION(function) std::bind(&Application::function, this, std::placeholders::_1)
    #define ADD_EVENT(event, function) window_->AddEvent(event, BIND_FUNCTION(function))

    Application::Application(int width, int height, std::string title)
    {
        window_ = new WinWindow(width, height, title);

        ADD_EVENT(WINDOW_CLOSE, OnWindowClose);
        ADD_EVENT(WINDOW_RESIZE, OnWindowResize);

        ADD_EVENT(MOUSE_MOVE, OnMouseMove);
        ADD_EVENT(MOUSE_CLICK, OnMouseClick);
        ADD_EVENT(MOUSE_SCROLL, OnMouseScroll);

        ADD_EVENT(KEY_PRESS, OnKeyPress);
        ADD_EVENT(KEY_RELEASE, OnKeyRelease);
    } 

    Application::~Application()
    {
        delete window_;
    }

    void Application::Run()
    {

    }

    void Application::Setup()
    {

    }

    void Application::OnWindowClose(Event& event)
    {

    }

    void Application::OnWindowResize(Event& event)
    {

    }

    void Application::OnMouseMove(Event& event)
    {

    }

    void Application::OnMouseClick(Event& event)
    {

    }

    void Application::OnMouseScroll(Event& event)
    {

    }

    void Application::OnKeyPress(Event& event)
    {

    }

    void Application::OnKeyRelease(Event& event)
    {

    }
} // namespace ntt

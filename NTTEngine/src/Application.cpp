#include <iostream>

#include <NTTEngine/Core.hpp>
#include <NTTEngine/Application.hpp>
#include <NTTEngine/Platforms/Platforms.hpp>
#include <NTTEngine/Macros.hpp>


namespace ntt
{
    Application* Application::application_ = nullptr;

    Application::Application(int width, int height, std::string title)
    {
        Application::SetApplication(this);
        window_ = new WinWindow(width, height, title);

        ADD_EVENT_APPLICATION(WindowClose);
        ADD_EVENT_APPLICATION(WindowResize);

        ADD_EVENT_APPLICATION(MouseMove);
        ADD_EVENT_APPLICATION(MouseClick);
        ADD_EVENT_APPLICATION(MouseScroll);

        ADD_EVENT_APPLICATION(KeyPress);
        ADD_EVENT_APPLICATION(KeyRelease);
    } 

    Application::~Application()
    {
        delete window_;
    }

    void Application::OnRun()
    {
        while(!window_->IsClosed())
        {
            OnUpdate();
        }
    }

    void Application::OnUpdate()
    {
        window_->OnUpdate();
        for (auto it=layerStack_.Begin(); it!=layerStack_.End(); it++)
        {
            (*it)->OnUpdate();
        }
        OnUpdateImpl();
    }

    void Application::OnUpdateImpl()
    {

    }

    void Application::OnSetup()
    {
        OnSetupImpl();
    }

    void Application::OnSetupImpl()
    {

    }

    DEFINE_EVENT_APPLICATION(WindowClose)
    DEFINE_EVENT_APPLICATION(WindowResize)

    DEFINE_EVENT_APPLICATION(MouseMove)
    DEFINE_EVENT_APPLICATION(MouseClick)
    DEFINE_EVENT_APPLICATION(MouseScroll)

    DEFINE_EVENT_APPLICATION(KeyPress)
    DEFINE_EVENT_APPLICATION(KeyRelease)

    // void Application::OnKeyRelease(Event& event) 
    // { 
    //     KeyReleaseEvent& e = static_cast<KeyReleaseEvent&>(event); 
    //     for (auto it=layerStack_.End() - 1; it != layerStack_.Begin() - 1; it--) 
    //     { 
    //         (*it)->OnKeyRelease(e); 
    //     } 
    //     OnKeyReleaseImpl(e); 
    // } 

    // void Application::OnKeyReleaseImpl(KeyReleaseEvent& event) 
    // {

    // }
} // namespace ntt

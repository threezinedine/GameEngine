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
        NTT_ENGINE_DEBUG("Delete Application");
    }

    void Application::OnRun()
    {
        while(!window_->IsClosed())
        {
            auto current = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> duration = current - start_;
            Timestep ts(duration.count());
            start_ = current;

            OnUpdate(ts);
        }
    }

    void Application::OnUpdate(Timestep ts)
    {
        window_->OnStartUpdate();
        window_->OnUpdate();
        layerStack_.OnUpdate(ts);
        OnUpdateImpl(ts);
        window_->OnEndUpdate();
    }

    void Application::OnUpdateImpl(Timestep ts)
    {

    }

    void Application::OnSetup()
    {
        start_ = std::chrono::high_resolution_clock::now();
        OnSetupImpl();
        RendererAPI::Init();
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

    // void Application::OnMouseMove(Event& event) 
    // { 
    //     MouseMoveEvent& e = static_cast<MouseMoveEvent&>(event); 
    //     for (auto it=layerStack_.End() - 1; it != layerStack_.Begin() - 1; it--) 
    //     { 
    //         (*it)->OnMouseMove(e); 
    //     } 
    //     OnMouseMoveImpl(e); 
    // } 

    // void Application::OnMouseMoveImpl(MouseMoveEvent& event) 
    // {

    // }
} // namespace ntt

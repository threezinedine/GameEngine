#include <iostream>

#include <NTTEngine/Core.hpp>
#include "NTTEngineLog/NTTEngineLog.hpp"
#include "NTTEngine/Application.hpp"
#include "NTTEngineWindow/NTTEngineWindow.hpp"
#include <NTTEngine/Macros.hpp>
#include "NTTEngine/Camera.hpp"


namespace ntt
{
    Application* Application::application_ = nullptr;

    Application::Application(int width, int height, std::string title)
    {
        NTT_ENGINE_DEBUG("Start Initialize the Application");
        Application::SetApplication(this);
        Window::Init(width, height, title);

        ADD_EVENT_APPLICATION(WindowClose);
        ADD_EVENT_APPLICATION(WindowResize);

        ADD_EVENT_APPLICATION(MouseMove);
        ADD_EVENT_APPLICATION(MouseClick);
        ADD_EVENT_APPLICATION(MouseScroll);

        ADD_EVENT_APPLICATION(KeyPress);
        ADD_EVENT_APPLICATION(KeyRelease);
        NTT_ENGINE_DEBUG("Finish Initialize the Application");
    } 

    Application::~Application()
    {
        NTT_ENGINE_DEBUG("Start Delete Application");
        RendererAPI::Release();
        NTT_ENGINE_DEBUG("Finish Delete Application");
    }

    void Application::OnRun()
    {
        while(!Window::GetInstance()->IsClosed())
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
        Window::GetInstance()->OnStartUpdate();
        Window::GetInstance()->OnUpdate();
        layerStack_.OnUpdate(ts);
        OnUpdateImpl(ts);
        Window::GetInstance()->OnEndUpdate();
    }

    void Application::OnUpdateImpl(Timestep ts)
    {

    }

    void Application::OnSetup()
    {
        start_ = std::chrono::high_resolution_clock::now();
        defaultCamera_ = std::make_shared<Camera>();
        OnSetupImpl();
        RendererAPI::Init();
    }

    void Application::OnSetupImpl()
    {

    }

    DEFINE_EVENT_APPLICATION(WindowClose)
    // DEFINE_EVENT_APPLICATION(WindowResize)
    void Application::OnWindowResize(Event& event) 
    { 
        WindowResizeEvent& e = static_cast<WindowResizeEvent&>(event); 
        for (auto it=layerStack_.End() - 1; it!=layerStack_.Begin() - 1; it--) 
        { 
            (*it)->OnWindowResize(e); 
        } 
        defaultCamera_->OnWindowResize(e);
        OnWindowResizeImpl(e);
    } 
    
    void Application::OnWindowResizeImpl(WindowResizeEvent& event) { }

    DEFINE_EVENT_APPLICATION(MouseMove)
    DEFINE_EVENT_APPLICATION(MouseClick)
    // DEFINE_EVENT_APPLICATION(MouseScroll)
    void Application::OnMouseScroll(Event& event) 
    { 
        MouseScrollEvent& e = static_cast<MouseScrollEvent&>(event); 
        for (auto it=layerStack_.End() - 1; it!=layerStack_.Begin() - 1; it--) 
        { 
            (*it)->OnMouseScroll(e); 
        } 
        defaultCamera_->OnMouseScroll(e);
        OnMouseScrollImpl(e); 
    } 
    
    void Application::OnMouseScrollImpl(MouseScrollEvent& event) { }

    DEFINE_EVENT_APPLICATION(KeyPress)
    DEFINE_EVENT_APPLICATION(KeyRelease)
} // namespace ntt

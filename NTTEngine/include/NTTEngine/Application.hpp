#pragma once
#include <string>

#include <NTTEngine/EventSystem/Event.hpp>
#include <NTTEngine/IWindow.hpp>


namespace ntt
{
    class Application
    {
        public:
            Application(int width, int height, std::string title);
            virtual ~Application();

            virtual void Setup();
            virtual void Run();

            virtual void OnWindowClose(Event& event);
            virtual void OnWindowResize(Event& event);

            virtual void OnMouseMove(Event& event);
            virtual void OnMouseClick(Event& event);
            virtual void OnMouseScroll(Event& event);

            virtual void OnKeyPress(Event& event);
            virtual void OnKeyRelease(Event& event);

        protected:
            IWindow* window_;
    }; 
} // namespace ntt

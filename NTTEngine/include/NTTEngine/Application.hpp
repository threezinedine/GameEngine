#pragma once
#include <string>

#include <NTTEngine/EventSystem/EventSystem.hpp>
#include <NTTEngine/IWindow.hpp>
#include <NTTEngine/Macros.hpp>
#include <NTTEngine/LayerStack.hpp>


namespace ntt
{
    class Application
    {
        public:
            Application(int width, int height, std::string title);
            virtual ~Application();

            virtual void OnSetup();
            virtual void OnUpdate();

        protected:
            DEFINE_EVENT_INTEFACE(WindowClose);
            DEFINE_EVENT_INTEFACE(WindowResize);

            DEFINE_EVENT_INTEFACE(MouseMove);
            DEFINE_EVENT_INTEFACE(MouseClick);
            DEFINE_EVENT_INTEFACE(MouseScroll);

            DEFINE_EVENT_INTEFACE(KeyPress);
            DEFINE_EVENT_INTEFACE(KeyRelease);

            IWindow* window_;
            LayerStack layerStack_;
        private:
    }; 
} // namespace ntt

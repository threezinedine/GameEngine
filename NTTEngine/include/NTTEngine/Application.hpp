#pragma once
#include <string>
#include <chrono>

#include <NTTEngine/EventSystem/EventSystem.hpp>
#include <NTTEngine/IWindow.hpp>
#include <NTTEngine/Macros.hpp>
#include <NTTEngine/LayerStack.hpp>
#include <NTTEngine/Renderer/Renderer.hpp>
#include <NTTEngine/Core/Core.hpp>


namespace ntt
{
    class Application
    {
        public:
            Application(int width, int height, std::string title);
            virtual ~Application();

            void OnSetup();
            void OnUpdate(Timestep ts);
            void OnRun();

            inline IWindow* GetWindow() const { return window_; }

            static Application* GetApplication()
            {
                return application_;
            }

            static void SetApplication(Application* application)
            {
                application_ = application;
            }

        protected:
            virtual void OnUpdateImpl(Timestep ts);
            virtual void OnSetupImpl();

            DEFINE_EVENT_INTEFACE(WindowClose);
            DEFINE_EVENT_INTEFACE(WindowResize);

            DEFINE_EVENT_INTEFACE(MouseMove);
            DEFINE_EVENT_INTEFACE(MouseClick);
            DEFINE_EVENT_INTEFACE(MouseScroll);

            DEFINE_EVENT_INTEFACE(KeyPress);
            DEFINE_EVENT_INTEFACE(KeyRelease);

            IWindow* window_;
            LayerStack layerStack_;
            std::shared_ptr<ntt::Camera> defaultCamera_;

        private:
            std::chrono::time_point<std::chrono::high_resolution_clock> start_;
            static Application* application_;
    }; 
} // namespace ntt

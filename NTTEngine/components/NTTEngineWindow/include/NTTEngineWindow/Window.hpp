#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <functional>

#include <GL/glew.h>
#include <glfw/glfw3.h>

#include "NTTEngineEventSystem/NTTEngineEventSystem.hpp"


namespace ntt
{
    class GraphicsContext;

    class Window
    {
        public:
            ~Window();

            void OnStartUpdate();
            void OnUpdate();
            void OnEndUpdate();
            inline unsigned int GetHeight() const { return height_; }
            inline unsigned int GetWidth() const { return width_; }
            inline void SetWindowSize(unsigned int width, unsigned int height) { width_ = width; height_ = height; }
            inline bool IsClosed() { return glfwWindowShouldClose(window_); }

            void SetVSync(bool enabled);
            inline bool IsSync() const { return sync_; }


            void AddEvent(EventType eventType, std::function<void(Event&)> callback)
            {
                dispatcher_.AddEvent(eventType, callback);
            }
            inline EventDispatcher GetDispatcher() const { return dispatcher_; }
            void* GetWindow() { return static_cast<void*>(window_); }

            static void Init(unsigned int height, unsigned int width, const std::string& title);
            static inline Window* GetInstance() { return instance_; }
            inline static void Release() { if (instance_ != nullptr) delete instance_; }

            static std::pair<int, int> GetMousePosition() { return instance_->GetMousePositionImpl(); }
            static bool IsButtonLeftClicked() { return instance_->IsButtonLeftClickedImpl(); }
            static bool IsKeyPressed(int key) { return instance_->IsKeyPressedImpl(key); }

        protected:
            Window(unsigned int height, unsigned int width, const std::string& title);
            std::pair<int, int> GetMousePositionImpl();
            bool IsButtonLeftClickedImpl();
            bool IsKeyPressedImpl(int key);

        private:
            GLFWwindow* window_;
            std::string title_;
            unsigned int height_;
            unsigned int width_;
            bool sync_;

            EventDispatcher dispatcher_;
            std::shared_ptr<GraphicsContext> context_ = nullptr;

            static Window* instance_;
    };
} // namespace ntt

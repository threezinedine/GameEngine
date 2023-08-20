#pragma once
#include <iostream>
#include <string>

#include <glfw/glfw3.h>

#include <NTTEngine/IWindow.hpp>


namespace ntt
{
    class WinWindow: public IWindow
    {
        public:
            WinWindow(unsigned int height, unsigned int width, std::string title);
            ~WinWindow();

            void OnStartUpdate() override;
            void OnUpdate() override;
            void OnEndUpdate() override;
            inline unsigned int GetHeight() const { return height_; }
            inline unsigned int GetWidth() const { return width_; }
            inline void SetWindowSize(unsigned int width, unsigned int height) { width_ = width; height_ = height; }
            inline bool IsClosed() { return glfwWindowShouldClose(window_); }

            void SetVSync(bool enabled) override;
            inline bool IsSync() const { return sync_; }

            void* GetWindow() override { return window_; }

        private:
            GLFWwindow* window_;
            std::string title_;
            unsigned int height_;
            unsigned int width_;
            bool sync_;
    };
} // namespace ntt

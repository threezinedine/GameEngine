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

            void OnUpdate() override;
            inline unsigned int GetHeight() const { return height_; }
            inline unsigned int GetWidth() const { return width_; }
            inline bool IsClosed() { return glfwWindowShouldClose(window_); }

            void SetVSync(bool enabled) override { sync_ = enabled; }
            inline bool IsSync() const { return sync_; }

        private:
            GLFWwindow* window_;
            std::string title_;
            unsigned int height_;
            unsigned int width_;
            bool sync_;
    };
} // namespace ntt

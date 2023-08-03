#include <iostream>

#include <GL/glew.h>
#include <glfw/glfw3.h>

#include <NTTEngine/Platforms/Windows/WinWindow.hpp>
#include <NTTEngine/Core.hpp>


namespace ntt
{
    WinWindow::WinWindow(unsigned int height, unsigned int width, std::string title)
        : height_(height), width_(width)
    {
        if (!glfwInit()) 
        {
            NTT_ENGINE_ERROR("Failed to initialize the gflw");
            exit(-1);
        }

        window_ = glfwCreateWindow(width_, height_, title.c_str(), nullptr, nullptr);
        if (!window_) 
        {
            NTT_ENGINE_ERROR("Failed to initialize the window");
            glfwTerminate();
            exit(-1);
        }

        glfwMakeContextCurrent(window_);

        if (glewInit() != GLEW_OK)
        {
            NTT_ENGINE_ERROR("Failed to initialize the glew");
            glfwTerminate();
            exit(-1);
        }
    } 

    WinWindow::~WinWindow()
    {
        glfwTerminate();
    }

    void WinWindow::OnUpdate()
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window_);

        glfwPollEvents();
    }
} // namespace ntt


#include <iostream>

#include <GL/glew.h>
#include <glfw/glfw3.h>

#include <NTTEngine/Platforms/Windows/WinWindow.hpp>
#include <NTTEngine/Core.hpp>
#include <NTTEngine/EventSystem/EventSystem.hpp>




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

        glfwSetWindowUserPointer(window_, this);

        glfwSetWindowCloseCallback(window_, [](GLFWwindow* window)
        {
            IWindow* win = static_cast<IWindow*>(glfwGetWindowUserPointer(window));
            WindowCloseEvent event; 
            win->GetDispatcher().Dispatch(event);
        });

        glfwSetCursorPosCallback(window_, [](GLFWwindow* window, double xpos, double ypos)
        {
            IWindow* win = static_cast<IWindow*>(glfwGetWindowUserPointer(window));
            MouseMoveEvent event((int)xpos, (int)ypos); 
            win->GetDispatcher().Dispatch(event);
        });

        glfwSetMouseButtonCallback(window_, [](GLFWwindow* window, int button, int action, int mods){
            IWindow* win = static_cast<IWindow*>(glfwGetWindowUserPointer(window));
            MouseClickEvent event(button, action, mods); 
            win->GetDispatcher().Dispatch(event);
        });

        glfwSetScrollCallback(window_, [](GLFWwindow* window, double xoffset, double yoffset)
        {
            IWindow* win = static_cast<IWindow*>(glfwGetWindowUserPointer(window));
            MouseScrollEvent event((int)xoffset, (int)yoffset); 
            win->GetDispatcher().Dispatch(event);
        });

        glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            IWindow* win = static_cast<IWindow*>(glfwGetWindowUserPointer(window));
            if (action == GLFW_PRESS)
            {
                KeyPressEvent event(key, mods);
                win->GetDispatcher().Dispatch(event);
            }
            else if (action == GLFW_RELEASE)
            {
                KeyReleaseEvent event(key, mods);
                win->GetDispatcher().Dispatch(event);
            }
        });

        glfwSetFramebufferSizeCallback(window_, [](GLFWwindow* window, int width, int height)
        {
            IWindow* win = static_cast<IWindow*>(glfwGetWindowUserPointer(window));
            WindowResizeEvent event(width, height);
            win->GetDispatcher().Dispatch(event);
        });
    } 

    WinWindow::~WinWindow()
    {
        glfwTerminate();
    }

    void WinWindow::OnUpdate()
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
        // glfwSwapBuffers(window_);
    }
} // namespace ntt


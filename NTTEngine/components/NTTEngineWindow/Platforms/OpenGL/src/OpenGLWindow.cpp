#include <iostream>

#include "OpenGLPreInclude.hpp"

#include "NTTEngineWindow/PreInclude.hpp"
#include "NTTEngineWindow/Window.hpp"


namespace ntt
{
    Window::Window(unsigned int height, unsigned int width, const std::string& title)
        : height_(height), width_(width)
    {
        PROFILE_SCOPE();

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
        

        context_ = std::make_shared<GraphicsContext>(window_);
        context_->Init();

        glfwSetWindowUserPointer(window_, this);

        glfwSetWindowCloseCallback(window_, [](GLFWwindow* window)
        {
            Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
            WindowCloseEvent event; 
            win->GetDispatcher().Dispatch(event);
        });

        glfwSetCursorPosCallback(window_, [](GLFWwindow* window, double xpos, double ypos)
        {
            Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
            MouseMoveEvent event((int)xpos, (int)ypos); 
            win->GetDispatcher().Dispatch(event);
        });

        glfwSetMouseButtonCallback(window_, [](GLFWwindow* window, int button, int action, int mods){
            Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
            MouseClickEvent event(button, action, mods); 
            win->GetDispatcher().Dispatch(event);
        });

        glfwSetScrollCallback(window_, [](GLFWwindow* window, double xoffset, double yoffset)
        {
            Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
            MouseScrollEvent event((int)xoffset, (int)yoffset); 
            win->GetDispatcher().Dispatch(event);
        });

        glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
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
            Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
            WindowResizeEvent event(width, height);
            win->SetWindowSize(width, height);
            win->GetDispatcher().Dispatch(event);
        });

        glfwMaximizeWindow(window_);
        glEnable(GL_DEPTH_TEST);
    } 

    Window::~Window()
    {
        PROFILE_SCOPE();

        glfwTerminate();
    }

    void Window::OnStartUpdate()
    {
        PROFILE_SCOPE();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();
    }

    void Window::OnEndUpdate()
    {
        PROFILE_SCOPE();

        glViewport(0, 0, width_, height_);
        context_->SwapBuffer();
    }

    void Window::SetVSync(bool sync)
    {
        if (sync)
        {
            glfwSwapInterval(1);
        }
        else 
        {
            glfwSwapInterval(0);
        }
    }

    std::pair<int, int> Window::GetMousePositionImpl()
    {
        double mouseX, mouseY;
        glfwGetCursorPos(window_, &mouseX, &mouseY);
        return std::make_pair((int)mouseX, (int)mouseY);
    }

    bool Window::IsButtonLeftClickedImpl()
    {
        return glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    }

    bool Window::IsKeyPressedImpl(int key)
    {
        return glfwGetKey(window_, key) == GLFW_PRESS;
    }

} // namespace ntt


#include <GL/glew.h>
#include <glfw/glfw3.h>

// #include <NTTEngine/Core.hpp>
#include "NTTEngineLog/NTTEngineLog.hpp"
#include "NTTEngineRenderer/NTTEngineRenderer.hpp"


namespace ntt
{
    GraphicsContext::GraphicsContext(GLFWwindow* window)
        : window_(window)
    {

    } 

    void GraphicsContext::Init()
    {
        glfwMakeContextCurrent(window_);

        if (glewInit() != GLEW_OK)
        {
            NTT_ENGINE_ERROR("Failed to initialize the glew");
            glfwTerminate();
            exit(-1);
        }

    }

    void GraphicsContext::SwapBuffer()
    {
        glfwSwapBuffers(window_);
    }
} // namespace ntt

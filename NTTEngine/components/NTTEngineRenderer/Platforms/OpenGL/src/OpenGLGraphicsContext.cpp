#include "OpenGLPreInclude.hpp"
#include "NTTEngineRenderer/PreInclude.hpp"
#include "NTTEngineRenderer/GraphicsContext.hpp"


namespace ntt
{
    GraphicsContext::GraphicsContext(GLFWwindow* window)
        : window_(window)
    {
        PROFILE_SCOPE();
    } 

    void GraphicsContext::Init()
    {
        PROFILE_SCOPE();
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

#include <GL/glew.h>
#include <glfw/glfw3.h>

#include <NTTEngine/Core.hpp>
#include <NTTEngine/Platforms/OpenGL/OpenGLContext.hpp>


namespace ntt
{
    OpenGLContext::OpenGLContext(GLFWwindow* window)
        : window_(window)
    {

    } 

    OpenGLContext::~OpenGLContext()
    {

    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(window_);

        if (glewInit() != GLEW_OK)
        {
            NTT_ENGINE_ERROR("Failed to initialize the glew");
            glfwTerminate();
            exit(-1);
        }

    }

    void OpenGLContext::SwapBuffer()
    {
        glfwSwapBuffers(window_);
    }
} // namespace ntt

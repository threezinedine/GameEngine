#include <GL/glew.h>
#include <glfw/glfw3.h>
#include <NTTEngine/Platforms/OpenGL/OpenGLVertexArray.hpp>
#include <NTTEngine/NTTEngine.hpp>


namespace ntt
{
    OpenGLVertexArray::OpenGLVertexArray() 
    {
        GL_CALL(glGenVertexArrays(1, &id_));
        Bind();
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        GL_CALL(glDeleteVertexArrays(1, &id_));
    }

    void OpenGLVertexArray::Bind()
    {
        GL_CALL(glBindVertexArray(id_));
    }

    void OpenGLVertexArray::UnBind()
    {
        GL_CALL(glBindVertexArray(0));
    }
} // namespace ntt

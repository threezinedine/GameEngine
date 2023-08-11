#include <GL/glew.h>
#include <glfw/glfw3.h>
#include <NTTEngine/Platforms/OpenGL/OpenGLVertexBuffer.hpp>
#include <NTTEngine/NTTEngine.hpp>


namespace ntt
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(float* data, unsigned int size)
    {
        GL_CALL(glGenBuffers(1, &id_));
        Bind();
        GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    } 

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        GL_CALL(glDeleteBuffers(1, &id_));
    }

    void OpenGLVertexBuffer::Bind()
    {
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, id_));
    }

    void OpenGLVertexBuffer::UnBind()
    {
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }
} // namespace ntt

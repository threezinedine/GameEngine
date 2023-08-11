#include <GL/glew.h>
#include <glfw/glfw3.h>
#include <NTTEngine/Platforms/OpenGL/OpenGLIndexBuffer.hpp>
#include <NTTEngine/NTTEngine.hpp>


namespace ntt
{
    OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* indeces, unsigned int size)
    {
        GL_CALL(glGenBuffers(1, &id_));
        Bind();
        GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indeces, GL_STATIC_DRAW));
    } 

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        GL_CALL(glDeleteBuffers(1, &id_));
    }

    void OpenGLIndexBuffer::Bind()
    {
        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_));
    }

    void OpenGLIndexBuffer::UnBind()
    {
        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }
} // namespace ntt

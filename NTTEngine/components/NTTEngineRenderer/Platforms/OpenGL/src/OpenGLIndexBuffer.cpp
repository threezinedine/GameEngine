#include "NTTEngineRenderer/PreInclude.hpp"
#include "NTTEngineRenderer/IndexBuffer.hpp"
#include "OpenGLPreInclude.hpp"


namespace ntt
{
    IndexBuffer::IndexBuffer(unsigned int* indeces, unsigned int size)
        : count_(size / sizeof(unsigned int))
    {
        GL_CALL(glGenBuffers(1, &id_));
        Bind();
        GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indeces, GL_STATIC_DRAW));
    } 

    IndexBuffer::~IndexBuffer()
    {
        GL_CALL(glDeleteBuffers(1, &id_));
    }

    void IndexBuffer::Bind()
    {
        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_));
    }

    void IndexBuffer::UnBind()
    {
        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

    void IndexBuffer::Render(int count)
    {
        int drawCount = !count ? count_ : count * 6 / 4;

        GL_CALL(glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, nullptr));
    }
} // namespace ntt

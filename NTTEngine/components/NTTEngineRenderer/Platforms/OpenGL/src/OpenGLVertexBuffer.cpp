#include "OpenGLPreInclude.hpp"
#include "NTTEngineRenderer/PreInclude.hpp"
#include "NTTEngineRenderer/VertexBuffer.hpp"
#include "NTTEngineRenderer/LayoutBuffer.hpp"


namespace ntt
{
    VertexBuffer::VertexBuffer(float* data, unsigned int size)
    {
        GL_CALL(glGenBuffers(1, &id_));
        Bind();
        GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    } 

    VertexBuffer::~VertexBuffer()
    {
        PROFILE_SCOPE();

        GL_CALL(glDeleteBuffers(1, &id_));
    }

    void VertexBuffer::Bind()
    {
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, id_));
    }

    void VertexBuffer::UnBind()
    {
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    void VertexBuffer::Setup()
    {
        for (int i=0; i<layouts_.size(); i++)
        {
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, layouts_[i].num, GL_FLOAT, 
                    layouts_[i].normalized, size_, (const void*)layouts_[i].offset);
        }
    }
} // namespace ntt

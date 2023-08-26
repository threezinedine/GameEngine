#include "OpenGLPreInclude.hpp"
#include "NTTEngineRenderer/PreInclude.hpp"
#include "NTTEngineRenderer/VertexBuffer.hpp"
#include "NTTEngineRenderer/LayoutBuffer.hpp"


namespace ntt
{
    VertexBuffer::VertexBuffer(unsigned int size)
        : useDynamic_(true)
    {
        GL_CALL(glGenBuffers(1, &id_));
        Bind();
        GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW));
    }

    VertexBuffer::VertexBuffer(float* data, unsigned int size)
        : useDynamic_(false)
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
                    layouts_[i].normalized, size_, reinterpret_cast<const void*>(layouts_[i].offset));
        }
    }

    void VertexBuffer::SetData(float* data, unsigned int count, unsigned int elementSize)
    {
        Bind();
        dynamicVertexsNum_ = count;
        glBufferSubData(GL_ARRAY_BUFFER, 0, count * elementSize, data);
    }
} // namespace ntt

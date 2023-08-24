#include <memory>
#include "OpenGLPreInclude.hpp"
#include "NTTEngineRenderer/PreInclude.hpp"
#include "NTTEngineRenderer/VertexArray.hpp"


namespace ntt
{
    VertexArray::VertexArray() 
    {
        GL_CALL(glGenVertexArrays(1, &id_));
        Bind();
    }

    VertexArray::~VertexArray()
    {
        PROFILE_SCOPE();
        GL_CALL(glDeleteVertexArrays(1, &id_));
    }

    void VertexArray::Bind()
    {
        GL_CALL(glBindVertexArray(id_));
    }

    void VertexArray::UnBind()
    {
        GL_CALL(glBindVertexArray(0));
    }
} // namespace ntt

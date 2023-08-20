#include <memory>
#include <GL/glew.h>
#include <glfw/glfw3.h>
#include "NTTEngineRenderer/NTTEngineRenderer.hpp"
#include "GL_ASSERTION.hpp"


namespace ntt
{
    VertexArray::VertexArray() 
    {
        GL_CALL(glGenVertexArrays(1, &id_));
        Bind();
    }

    VertexArray::~VertexArray()
    {
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

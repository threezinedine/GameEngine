#include "NTTEngineRenderer/NTTEngineRenderer.hpp"


namespace ntt
{
    void VertexArray::AppendVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer)
    {
        buffer->Bind();
        buffer->Setup();
        vertexBuffers_.push_back(buffer);
    }

    void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& index)
    {
        index->Bind();
        indexBuffer_ = index;
    }
} // namespace ntt

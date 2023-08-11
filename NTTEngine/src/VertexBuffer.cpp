#include <NTTEngine/Renderer/VertexBuffer.hpp>


namespace ntt
{
    void VertexBuffer::RegisterBuffer(LayoutBuffer buffer)
    {
        buffer.offset = size_;
        size_ += buffer.size;
        layouts_.push_back(buffer);
    }
} // namespace ntt

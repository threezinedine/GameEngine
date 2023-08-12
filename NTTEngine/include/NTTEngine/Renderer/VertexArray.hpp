#pragma once
#include <memory>
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"


namespace ntt
{
    class VertexArray
    {
        public:
            virtual ~VertexArray() = default;

            virtual void Bind() = 0;
            virtual void UnBind() = 0;

            void AppendVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer);
            void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& index);

            inline const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return vertexBuffers_; }
            inline const std::shared_ptr<IndexBuffer>& GetIndexBuffers() const { return indexBuffer_; }

        private:
            std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers_;
            std::shared_ptr<IndexBuffer> indexBuffer_;
    }; 
} // namespace ntt
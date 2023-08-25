#pragma once
#include <memory>

namespace ntt
{
    class VertexBuffer;
    class IndexBuffer;

    class VertexArray
    {
        public:
            VertexArray();
            virtual ~VertexArray();

            virtual void Bind();
            virtual void UnBind();

            void AppendVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer);
            void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& index);

            inline const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return vertexBuffers_; }
            inline const std::shared_ptr<IndexBuffer>& GetIndexBuffers() const { return indexBuffer_; }

        private:
            std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers_;
            std::shared_ptr<IndexBuffer> indexBuffer_;


            // #ifdef OPENGL_PLATFORM
            unsigned int id_;
            // #endif
    }; 
} // namespace ntt
#pragma once
#include <vector>


namespace ntt
{
    class LayoutBuffer;

    class VertexBuffer
    {
        public:
            VertexBuffer(float* data, unsigned int size);
            virtual ~VertexBuffer();

            virtual void Bind();
            virtual void UnBind();

            void RegisterBuffer(LayoutBuffer buffer);

            virtual void Setup();

        protected:
            std::vector<LayoutBuffer> layouts_;
            unsigned int size_ = 0;
            unsigned int id_;
    }; 
} // namespace ntt

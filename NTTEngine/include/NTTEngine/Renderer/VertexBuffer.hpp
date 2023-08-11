#pragma once
#include <vector>
#include "LayoutBuffer.hpp"


namespace ntt
{
    class VertexBuffer
    {
        public:
            virtual ~VertexBuffer() = default;

            virtual void Bind() = 0;
            virtual void UnBind() = 0;

            void RegisterBuffer(LayoutBuffer buffer);
            virtual void Setup() = 0;

        protected:
            std::vector<LayoutBuffer> layouts_;
            unsigned int size_ = 0;
    }; 
} // namespace ntt

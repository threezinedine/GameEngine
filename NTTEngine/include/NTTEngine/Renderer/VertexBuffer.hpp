#pragma once


namespace ntt
{
    class VertexBuffer
    {
        public:
            virtual ~VertexBuffer() = default;

            virtual void Bind() = 0;
            virtual void UnBind() = 0;
    }; 
} // namespace ntt

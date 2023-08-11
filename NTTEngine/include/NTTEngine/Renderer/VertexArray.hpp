#pragma once


namespace ntt
{
    class VertexArray
    {
        public:
            virtual ~VertexArray() = default;

            virtual void Bind() = 0;
            virtual void UnBind() = 0;
    }; 
} // namespace ntt
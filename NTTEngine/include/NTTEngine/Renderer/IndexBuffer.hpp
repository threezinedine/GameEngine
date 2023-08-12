#pragma once


namespace ntt
{
    class IndexBuffer
    {
        public:
            virtual ~IndexBuffer() = default;

            virtual void Bind() = 0;
            virtual void UnBind() = 0;

            virtual int GetCount() const = 0;
    }; 
} // namespace ntt

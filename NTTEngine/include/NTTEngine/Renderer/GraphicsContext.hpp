#pragma once


namespace ntt
{
    class GraphicsContext
    {
        public:
            virtual void Init() = 0;
            virtual void SwapBuffer() = 0;
    }; 
} // namespace ntt

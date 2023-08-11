#pragma once
#include "NTTEngine/Renderer/VertexBuffer.hpp"


namespace ntt
{
    class OpenGLVertexBuffer: public VertexBuffer
    {
        public:
            OpenGLVertexBuffer(float* data, unsigned int size);
            ~OpenGLVertexBuffer();

            void Bind() override;
            void UnBind() override;

            void Setup() override;

        private:
            unsigned int id_;
    };
} // namespace ntt

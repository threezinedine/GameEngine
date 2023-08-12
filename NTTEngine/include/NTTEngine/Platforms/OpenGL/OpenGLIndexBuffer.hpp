#pragma once

#include "NTTEngine/Renderer/IndexBuffer.hpp"


namespace ntt
{
    class OpenGLIndexBuffer: public IndexBuffer
    {
        public:
            OpenGLIndexBuffer(unsigned int* indeces, unsigned int size);
            ~OpenGLIndexBuffer();

            void Bind() override;
            void UnBind() override;

            inline int GetCount() const override { return count_; };
            void Render() override;

        private:
            unsigned int id_;
            int count_;
    };
} // namespace ntt

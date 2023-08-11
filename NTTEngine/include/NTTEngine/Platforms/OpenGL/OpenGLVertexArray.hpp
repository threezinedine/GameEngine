#pragma once
#include <NTTEngine/Renderer/VertexArray.hpp>


namespace ntt
{
    class OpenGLVertexArray: public VertexArray
    {
        public:
            OpenGLVertexArray();
            ~OpenGLVertexArray();

            void Bind() override;
            void UnBind() override;

        private:    
            unsigned int id_;
    };
} // namespace ntt

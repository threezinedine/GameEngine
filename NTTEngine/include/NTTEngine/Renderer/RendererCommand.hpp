#pragma once
#include <memory>
#include "Shader.hpp"
#include "VertexArray.hpp"



namespace ntt
{
    class RendererCommand
    {
        public: 
            static void DrawIndex(std::shared_ptr<VertexArray>& vertexArray, 
                                    std::shared_ptr<Shader> shader);
    }; 
} // namespace ntt

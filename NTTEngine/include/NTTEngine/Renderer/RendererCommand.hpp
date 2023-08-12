#pragma once
#include <memory>
#include "VertexArray.hpp"



namespace ntt
{
    class RendererCommand
    {
        public: 
            static void DrawIndex(std::shared_ptr<VertexArray>& vertexArray);
    }; 
} // namespace ntt

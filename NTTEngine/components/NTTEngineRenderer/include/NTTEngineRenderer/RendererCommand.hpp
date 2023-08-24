#pragma once
#include <memory>



namespace ntt
{
    class VertexArray;
    class Shader;

    class RendererCommand
    {
        public: 
            static void DrawIndex(std::shared_ptr<VertexArray>& vertexArray, 
                                    std::shared_ptr<Shader> shader,
                                    glm::mat4 transform);
    }; 
} // namespace ntt

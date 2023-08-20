#include "NTTEngineRenderer/NTTEngineRenderer.hpp"


namespace ntt
{
    void RendererCommand::DrawIndex(std::shared_ptr<VertexArray>& vertexArray,
                                        std::shared_ptr<Shader> shader,
                                        glm::mat4 transform) 
    {
        RendererAPI::GetInstance()->DrawIndex(vertexArray, shader, transform);
    }
} // namespace ntt

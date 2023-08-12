#include "NTTEngine/Renderer/RendererAPI.hpp"
#include "NTTEngine/Renderer/RendererCommand.hpp"


namespace ntt
{
    void RendererCommand::DrawIndex(std::shared_ptr<VertexArray>& vertexArray,
                                        std::shared_ptr<Shader> shader) 
    {
        RendererAPI::GetInstance()->DrawIndex(vertexArray, shader);
    }
} // namespace ntt

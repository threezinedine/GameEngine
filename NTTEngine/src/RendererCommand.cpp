#include "NTTEngine/Renderer/RendererAPI.hpp"
#include "NTTEngine/Renderer/RendererCommand.hpp"


namespace ntt
{
    void RendererCommand::DrawIndex(std::shared_ptr<VertexArray>& vertexArray) 
    {
        RendererAPI::GetInstance()->DrawIndex(vertexArray);
    }
} // namespace ntt

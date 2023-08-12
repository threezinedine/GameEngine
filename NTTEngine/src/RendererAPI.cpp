#include "NTTEngine/Renderer/RendererAPI.hpp"
#include "NTTEngine/Renderer/RendererCommand.hpp"


namespace ntt
{
    RendererAPI* RendererAPI::instance_ = nullptr;

    RendererAPI::RendererAPI()
    {
        RendererAPI::instance_ = this;
    }

    RendererAPI::~RendererAPI()
    {

    } 

    void RendererAPI::Begin()
    {

    }

    void RendererAPI::Submit(std::shared_ptr<VertexArray>& vertexArray)
    {
        RendererCommand::DrawIndex(vertexArray);
    }

    void RendererAPI::End()
    {

    }

    void RendererAPI::DrawIndex(std::shared_ptr<VertexArray>& vertexArray)
    {
        vertexArray->Bind();
        vertexArray->GetIndexBuffers()->Render();
    }

    RendererAPI* RendererAPI::GetInstance()
    {
        if (instance_ == nullptr)
        {
            instance_ = new RendererAPI();
        }

        return instance_;
    }
} // namespace ntt

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

    void RendererAPI::Begin(std::shared_ptr<Camera>& camera)
    {
        GetInstance()->SetCamera(camera);
    }

    void RendererAPI::Submit(std::shared_ptr<VertexArray>& vertexArray, 
                                std::shared_ptr<Shader>& shader,
                                glm::mat4 transform)
    {
        RendererCommand::DrawIndex(vertexArray, shader, transform);
    }

    void RendererAPI::End()
    {

    }

    void RendererAPI::DrawIndex(std::shared_ptr<VertexArray>& vertexArray,
                                    std::shared_ptr<Shader>& shader,
                                    glm::mat4 transform)
    {
        shader->Bind();
        auto projViewMatrix = camera_->GetViewProjectMatrix();
        shader->SetUniformMat4f("projView", projViewMatrix);
        shader->SetUniformMat4f("transform", transform);

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

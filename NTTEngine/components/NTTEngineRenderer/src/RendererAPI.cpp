#include "NTTEngineLog/NTTEngineLog.hpp"
#include "NTTEngineRenderer/NTTEngineRenderer.hpp"


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

    void RendererAPI::Begin(std::shared_ptr<Camera>& camera, Timestep ts)
    {
        GetInstance()->SetCamera(camera);
        camera->OnUpdate(ts);
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

    void RendererAPI::Release()
    {
        NTT_ENGINE_DEBUG("Release RendererAPI");
        if (instance_ != nullptr)
        {
            delete instance_;
        }
    }
} // namespace ntt

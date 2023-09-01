#include "NTTEngineRenderer/PreInclude.hpp"
#include "NTTEngineRenderer/RendererAPI.hpp"
#include "NTTEngineRenderer/Camera.hpp"
#include "NTTEngineRenderer/RendererCommand.hpp"
#include "NTTEngineRenderer/Shader.hpp"
#include "NTTEngineRenderer/VertexArray.hpp"
#include "NTTEngineRenderer/IndexBuffer.hpp"
#include "NTTEngineRenderer/VertexBuffer.hpp"
#include "NTTEngineWindow/NTTEngineWindow.hpp"


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
        PROFILE_SCOPE();
        GetInstance()->SetCamera(camera);
        camera->OnUpdate(ts);
    }

    void RendererAPI::Submit(std::shared_ptr<VertexArray>& vertexArray, 
                                std::shared_ptr<Shader>& shader,
                                glm::mat4 transform)
    {
        RendererCommand::DrawIndex(vertexArray, shader, transform);
    }

    void RendererAPI::Clear()
    {
        instance_->ClearIn();
    }

    void RendererAPI::End()
    {

    }

    void RendererAPI::DrawIndex(std::shared_ptr<VertexArray>& vertexArray,
                                    std::shared_ptr<Shader>& shader,
                                    glm::mat4 transform)
    {
        PROFILE_SCOPE();
        auto projViewMatrix = camera_->GetViewProjectMatrix();
        shader->SetUniformMat4f("projView", projViewMatrix);
        // glm::mat4 projectView = glm::mat4(1.0f);
        // shader->SetUniformMat4f("projView", projectView);
        shader->SetUniformMat4f("transform", transform);

        vertexArray->Bind();
        if (vertexArray->GetVertexBuffers()[0]->IsDynamic())
        {
            vertexArray->GetIndexBuffers()->Render(vertexArray->GetVertexBuffers()[0]->GetDynamicVertexesNum());
        }
        else 
        {
            vertexArray->GetIndexBuffers()->Render();
        }
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
        PROFILE_SCOPE();
        if (instance_ != nullptr)
        {
            delete instance_;
        }
    }

    void RendererAPI::ClearIn()
    {
        Window::Clear();
    }
} // namespace ntt

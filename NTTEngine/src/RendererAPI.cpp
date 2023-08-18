#include "GL/glew.h"
#include "glfw/glfw3.h"
#include "NTTEngine/Renderer/RendererAPI.hpp"
#include "NTTEngine/Renderer/RendererCommand.hpp"
#include "NTTEngine/Core/Core.hpp"


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

    void RendererAPI::Init()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
        if (instance_ != nullptr)
        {
            delete instance_;
        }
    }
} // namespace ntt

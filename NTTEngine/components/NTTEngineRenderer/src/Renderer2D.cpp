#include "NTTEngineRenderer/NTTEngineRenderer.hpp"


namespace ntt
{
    Renderer2D* Renderer2D::instance_ = new Renderer2D(); 

    void Renderer2D::Init()
    {
        instance_->InitIn();
    }

    void Renderer2D::InitIn()
    {
        float vertices[] = 
        {
            -0.5f, -0.5f,
             0.5f, -0.5f,
             0.5f,  0.5f,
            -0.5f,  0.5f,
        };

        unsigned int indexes[] = 
        { 
            0, 1, 2, 
            2, 3, 0,
        };

        vao_ = std::make_shared<ntt::VertexArray>();

        auto vbo_ = std::make_shared<ntt::VertexBuffer>(vertices, sizeof(vertices));
        vbo_->RegisterBuffer(ntt::LayoutBuffer(ntt::Float2, std::string("position")));
        vao_->AppendVertexBuffer(vbo_);

        auto vio_ = std::make_shared<ntt::IndexBuffer>(indexes, sizeof(indexes));
        vao_->SetIndexBuffer(vio_);

        shader_ = std::make_shared<ntt::Shader>(std::string("../resources/shaders/basic.shader"),
                                std::string("vertex"), std::string("fragment"));
    }

    void Renderer2D::Release()
    {
        if (instance_ != nullptr)
        {
            delete instance_;
        }
    }

    void Renderer2D::BeginScence(std::shared_ptr<Camera> camera, Timestep ts)
    {
        RendererAPI::Begin(camera, ts);
    }

    void Renderer2D::End()
    {

    }

    void Renderer2D::DrawQuad(glm::vec2 position, glm::vec2 size, glm::vec3& color)
    {
        instance_->DrawQuadIn(position, size, color);
    }

    void Renderer2D::DrawQuadIn(glm::vec2 position, glm::vec2 size, glm::vec3& color)
    {
        shader_->SetUniform3f("m_Color", color);
        RendererAPI::Submit(vao_, shader_);
    }
} // namespace ntt

#include <glm/gtc/matrix_transform.hpp>
#include <opencv2/opencv.hpp>
#include "NTTEngineRenderer/PreInclude.hpp"
#include "NTTEngineRenderer/Renderer2D.hpp"
#include "NTTEngineRenderer/VertexBuffer.hpp"
#include "NTTEngineRenderer/VertexArray.hpp"
#include "NTTEngineRenderer/LayoutBuffer.hpp"
#include "NTTEngineRenderer/IndexBuffer.hpp"
#include "NTTEngineRenderer/RendererAPI.hpp"
#include "NTTEngineRenderer/Texture.hpp"
#include "NTTEngineRenderer/Shader.hpp"


namespace ntt
{
    Renderer2D* Renderer2D::instance_ = new Renderer2D(); 

    void Renderer2D::Init()
    {
        PROFILE_SCOPE();

        instance_->InitIn();
    }

    void Renderer2D::InitIn()
    {
        float vertices[] = 
        {
            -0.5f, -0.5f, 0.0f, 0.0f,
             0.5f, -0.5f, 1.0f, 0.0f,
             0.5f,  0.5f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 1.0f,
        };

        unsigned int indexes[] = 
        { 
            0, 1, 2, 
            2, 3, 0,
        };

        vao_ = std::make_shared<ntt::VertexArray>();

        auto vbo_ = std::make_shared<ntt::VertexBuffer>(vertices, sizeof(vertices));
        vbo_->RegisterBuffer(ntt::LayoutBuffer(ntt::Float2, std::string("position")));
        vbo_->RegisterBuffer(ntt::LayoutBuffer(ntt::Float2, std::string("coord")));
        vao_->AppendVertexBuffer(vbo_);

        auto vio_ = std::make_shared<ntt::IndexBuffer>(indexes, sizeof(indexes));
        vao_->SetIndexBuffer(vio_);

        shader_ = std::make_shared<ntt::Shader>(std::string("../resources/shaders/basic.shader"),
                                std::string("vertex"), std::string("all-fragment"));
        whiteTexture_ = std::make_shared<ntt::Texture2D>(300, 300);
        cv::Mat whiteImage = cv::Mat::ones(300, 300, CV_8UC3);
        whiteImage.setTo(cv::Scalar(255.0, 255.0, 255.0));
        whiteTexture_->SetData(whiteImage);
        
        shader_->Bind();
        shader_->SetUniform1i("m_Texture", 0);
    }

    void Renderer2D::Release()
    {
        PROFILE_SCOPE();

        if (instance_ != nullptr)
        {
            delete instance_;
        }
    }

    void Renderer2D::BeginScence(std::shared_ptr<Camera> camera, Timestep ts)
    {
        PROFILE_SCOPE();

        RendererAPI::Begin(camera, ts);
    }

    void Renderer2D::End()
    {
        PROFILE_SCOPE();
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec3& color)
    {
        PROFILE_SCOPE();
        instance_->DrawQuadIn(position, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color)
    {
        PROFILE_SCOPE();
        instance_->DrawQuadIn({ position.x, position.y, 0.0f }, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture, float tilingFactor, const glm::vec4& tintColor)
    {
        PROFILE_SCOPE();
        instance_->DrawQuadIn({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture, float tilingFactor, const glm::vec4& tintColor)
    {
        instance_->DrawQuadIn(position, size, texture, tilingFactor, tintColor);
    }


    void Renderer2D::DrawRotateQuad(const glm::vec2& position, const glm::vec2& size, float rotate, const glm::vec3& color)
    {
        instance_->DrawRotateQuadIn({ position.x, position.y, 0}, size, rotate, color);
    }

    void Renderer2D::DrawRotateQuad(const glm::vec3& position, const glm::vec2& size, float rotate, const glm::vec3& color)
    {
        instance_->DrawRotateQuadIn(position, size, rotate, color);
    }

    void Renderer2D::DrawRotateQuad(const glm::vec2& position, const glm::vec2& size, float rotate, const std::shared_ptr<Texture>& texture, float tilingFactor, const glm::vec4& tintColor)
    {
        instance_->DrawRotateQuadIn({ position.x, position.y, 0.0f }, size, rotate, texture, tilingFactor, tintColor);
    }

    void Renderer2D::DrawRotateQuad(const glm::vec3& position, const glm::vec2& size, float rotate, const std::shared_ptr<Texture>& texture, float tilingFactor, const glm::vec4& tintColor)
    {
        instance_->DrawRotateQuadIn(position, size, rotate, texture, tilingFactor, tintColor);
    }


    void Renderer2D::DrawQuadIn(const glm::vec3& position, const glm::vec2& size, const glm::vec3& color)
    {
        whiteTexture_->Bind();
        shader_->SetUniform1f("m_TilingFactor", 1.0f);
        shader_->SetUniform4f("m_Color", color);

        glm::mat4 transform = glm::translate(glm::mat4(1.0), position)
                * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

        RendererAPI::Submit(vao_, shader_, transform);
    }

    void Renderer2D::DrawQuadIn(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture, float tilingFactor, const glm::vec4& tintColor)
    {
        texture->Bind();
        shader_->SetUniform1f("m_TilingFactor", tilingFactor);
        shader_->SetUniform4f("m_Color", tintColor);

        glm::mat4 transform = glm::translate(glm::mat4(1.0), position)
                * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

        RendererAPI::Submit(vao_, shader_, transform);
    }

    void Renderer2D::DrawRotateQuadIn(const glm::vec3& position, const glm::vec2& size, float rotate, const glm::vec3& color)
    {
        whiteTexture_->Bind();
        shader_->SetUniform1f("m_TilingFactor", 1.0f);
        shader_->SetUniform4f("m_Color", color);

        glm::mat4 transform = glm::translate(glm::mat4(1.0), position)
                * glm::rotate(glm::mat4(1.0f), glm::radians(rotate), { 0.0f, 0.0f, 1.0f })
                * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

        RendererAPI::Submit(vao_, shader_, transform); 
    }

    void Renderer2D::DrawRotateQuadIn(const glm::vec3& position, const glm::vec2& size, float rotate, const std::shared_ptr<Texture>& texture, float tilingFactor, const glm::vec4& tintColor)
    {
        shader_->SetUniform1f("m_TilingFactor", tilingFactor);
        shader_->SetUniform4f("m_Color", tintColor);
        texture->Bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0), position)
                * glm::rotate(glm::mat4(1.0f), glm::radians(rotate), { 0.0f, 0.0f, 1.0f })
                * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

        RendererAPI::Submit(vao_, shader_, transform);
    }

} // namespace ntt

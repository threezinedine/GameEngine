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
        unsigned int indexes[MAX_INDEX_BUFFER];

        int offset = 0;

        for (int i=0; i<MAX_INDEX_BUFFER; i+=6)
        {
            indexes[i + 0] = offset + 0;
            indexes[i + 1] = offset + 1;
            indexes[i + 2] = offset + 2;

            indexes[i + 3] = offset + 2;
            indexes[i + 4] = offset + 3;
            indexes[i + 5] = offset + 0;

            offset += 4;
        }

        vao_ = std::make_shared<ntt::VertexArray>();

        auto vbo_ = std::make_shared<ntt::VertexBuffer>(MAX_VERTEX_BUFFER * sizeof(VertexData));
        vbo_->RegisterBuffer(ntt::LayoutBuffer(ntt::Float3, std::string("position")));
        vbo_->RegisterBuffer(ntt::LayoutBuffer(ntt::Float4, std::string("color")));
        vbo_->RegisterBuffer(ntt::LayoutBuffer(ntt::Float2, std::string("coord")));
        vbo_->RegisterBuffer(ntt::LayoutBuffer(ntt::Float, std::string("textureId")));
        vao_->AppendVertexBuffer(vbo_);

        auto vio_ = std::make_shared<ntt::IndexBuffer>(indexes, sizeof(indexes));
        vao_->SetIndexBuffer(vio_);

        vertexDatas_ = new VertexData[MAX_BATCH];

        shader_ = std::make_shared<ntt::Shader>(std::string("../resources/shaders/basic.shader"),
                                std::string("vertex"), std::string("all-fragment"));
        whiteTexture_ = std::make_shared<ntt::Texture2D>(300, 300);
        cv::Mat whiteImage = cv::Mat::ones(300, 300, CV_8UC3);
        whiteImage.setTo(cv::Scalar(255.0, 255.0, 255.0));
        whiteTexture_->SetData(whiteImage);
        whiteTexture_->Bind();
        
        shader_->Bind();

        int textArray[MAX_TEXTURE_SLOT];
        for (int i=0; i<MAX_TEXTURE_SLOT; i++)
        {
            textArray[i] = i;
        }

        shader_->SetUniformIntArray("m_TextureArray", textArray, MAX_TEXTURE_SLOT);
    }

    void Renderer2D::Release()
    {
        PROFILE_SCOPE();
        instance_->ReleaseIn();

        if (instance_ != nullptr)
        {
            delete instance_;
        }
    }

    void Renderer2D::ReleaseIn()
    {
        delete[] vertexDatas_;
    }

    void Renderer2D::BeginScene(std::shared_ptr<Camera> camera, Timestep ts)
    {
        PROFILE_SCOPE();

        RendererAPI::Begin(camera, ts);
        instance_->BeginSceneIn();
    }

    void Renderer2D::BeginSceneIn()
    {
        ptr_ = vertexDatas_;
        textures_.clear();
        textures_.push_back(whiteTexture_);
    }

    void Renderer2D::EndScene()
    {
        PROFILE_SCOPE();
        instance_->EndSceneIn();
    }

    void Renderer2D::EndSceneIn()
    {
        PROFILE_SCOPE();

        unsigned int count = ptr_ - vertexDatas_;
        for (int i=0; i<textures_.size(); i++)
        {
            textures_[i]->Bind(i);
        }

        vao_->GetVertexBuffers()[0]->SetData((float*)vertexDatas_, count, sizeof(VertexData));
        RendererAPI::Submit(vao_, shader_);

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
        shader_->SetUniform1f("m_TilingFactor", 1.0f);

        auto transform = glm::translate(glm::mat4(1.0f), position)
                        * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        DrawIn(position, color, 0.0f, transform);
    }

    void Renderer2D::DrawQuadIn(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture, float tilingFactor, const glm::vec4& tintColor)
    {
        float texIndex = 0;

        for (int i=0; i<textures_.size(); i++)
        {
            if (texture->EqualTo(textures_[i]))
            {
                texIndex = (float)i;
            }
        }

        if (texIndex == 0)
        {
            texIndex = (float)textures_.size();
            textures_.push_back(texture);
        }

        shader_->SetUniform1f("m_TilingFactor", 1.0f);

        auto transform = glm::translate(glm::mat4(1.0f), position)
                        * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        DrawIn(position, tintColor, texIndex, transform);

#ifdef OLD_PATH
        texture->Bind();
        shader_->SetUniform1f("m_TilingFactor", tilingFactor);
        shader_->SetUniform4f("m_Color", tintColor);

        glm::mat4 transform = glm::translate(glm::mat4(1.0), position)
                * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

        RendererAPI::Submit(vao_, shader_, transform);
#endif
    }


    void Renderer2D::DrawIn(const glm::vec3& position, const glm::vec3& color, float texIndex, const glm::mat4& transform)
    {
        auto vec4Color = glm::vec4(color.x, color.y, color.z, 1.0f);

        ptr_->position = transform * glm::vec4(-0.5f, -0.5f, position.z , 1.0f);
        ptr_->color = vec4Color;
        ptr_->coord = glm::vec2(0.0f, 0.0f);
        ptr_->texIndex = texIndex;
        ptr_++;

        ptr_->position = transform * glm::vec4(0.5f, -0.5f, position.z , 1.0f);
        ptr_->color = vec4Color;
        ptr_->coord = glm::vec2(1.0f, 0.0f);
        ptr_->texIndex = texIndex;
        ptr_++;

        ptr_->position = transform * glm::vec4(0.5f, 0.5f, position.z , 1.0f);
        ptr_->color = vec4Color;
        ptr_->coord = glm::vec2(1.0f, 1.0f);
        ptr_->texIndex = texIndex;
        ptr_++;

        ptr_->position = transform * glm::vec4(-0.5f, 0.5f, position.z , 1.0f);
        ptr_->color = vec4Color;
        ptr_->coord = glm::vec2(0.0f, 1.0f);
        ptr_->texIndex = texIndex;
        ptr_++;

    }

    void Renderer2D::DrawRotateQuadIn(const glm::vec3& position, const glm::vec2& size, float rotate, const glm::vec3& color)
    {
        shader_->SetUniform1f("m_TilingFactor", 1.0f);

        glm::mat4 transform = glm::translate(glm::mat4(1.0), position)
                * glm::rotate(glm::mat4(1.0f), glm::radians(rotate), { 0.0f, 0.0f, 1.0f })
                * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

        DrawIn(position, color, 0.0f, transform);
    }

    void Renderer2D::DrawRotateQuadIn(const glm::vec3& position, const glm::vec2& size, float rotate, const std::shared_ptr<Texture>& texture, float tilingFactor, const glm::vec4& tintColor)
    {
        float texIndex = 0;

        for (int i=0; i<textures_.size(); i++)
        {
            if (texture->EqualTo(textures_[i]))
            {
                texIndex = (float)i;
            }
        }

        if (texIndex == 0)
        {
            texIndex = (float)textures_.size();
            textures_.push_back(texture);
        }

        shader_->SetUniform1f("m_TilingFactor", tilingFactor);

        glm::mat4 transform = glm::translate(glm::mat4(1.0), position)
                * glm::rotate(glm::mat4(1.0f), glm::radians(rotate), { 0.0f, 0.0f, 1.0f })
                * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

        DrawIn(position, tintColor, texIndex, transform);
    }

} // namespace ntt

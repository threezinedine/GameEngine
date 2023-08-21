#include <memory>
#include "Renderer2DLayer.hpp"


Renderer2DLayer::Renderer2DLayer(std::shared_ptr<ntt::Camera>& camera)
    : Layer("2DRendererLayer"), camera_(camera)
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
    vbo_->RegisterBuffer(ntt::LayoutBuffer(ntt::Float2, std::string("texture")));
    vao_->AppendVertexBuffer(vbo_);

    auto vio_ = std::make_shared<ntt::IndexBuffer>(indexes, sizeof(indexes));
    vao_->SetIndexBuffer(vio_);

    storage_ = std::make_shared<ntt::Storage>(
        std::make_shared<ntt::RealFileSystem>("./" + GetName() + "-layer.json"));

    squareColor_ = 
        std::make_unique<ntt::NTTVec3>(
            std::vector<float>{0, 0, 0}, storage_, "squareColor"
        );

    shader_ = std::make_shared<ntt::Shader>(std::string("../resources/shaders/basic.shader"),
                            std::string("vertex"), std::string("fragment"));
}

Renderer2DLayer::~Renderer2DLayer()
{
    squareColor_->Save(); 
    storage_->Save();
}

void Renderer2DLayer::OnUpdate(ntt::Timestep ts)
{
    ntt::RendererAPI::Begin(camera_, ts);

    shader_->SetUniform3f("m_Color", squareColor_->GetGlmVec3());
    ntt::RendererAPI::Submit(vao_, shader_);

    ntt::RendererAPI::End();
}


void Renderer2DLayer::OnImGuiRenderImpl(ntt::Timestep ts)
{
    ImGui::ColorPicker3("Squared Color", squareColor_->GetFirstPointer());
    camera_->OnImGuiRender(ts);
}

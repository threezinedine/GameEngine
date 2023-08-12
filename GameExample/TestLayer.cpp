#include <GL/glew.h>
#include <glfw/glfw3.h>
#include "TestLayer.hpp"
#include <NTTEngine/NTTEngine.hpp>


TestLayer::TestLayer()
    : Layer("Test Layer")
{
    float vertices[] = 
    {
        -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
         0.5f,  0.5f, 1.0f, 1.0f, 0.0f,
    };

    unsigned int indexes[] = 
    { 
        0, 1, 2, 
        1, 2, 3,
    };

    float triangleVertices[] = 
    {
        -0.5f, -0.3f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.4f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.0f, 0.0f, 0.0f, 1.0f,
    };

    unsigned int triangleIndexes[] = 
    { 
        0, 1, 2, 
    };

    vao_ = std::make_shared<ntt::OpenGLVertexArray>();

    auto vbo_ = std::make_shared<ntt::OpenGLVertexBuffer>(vertices, sizeof(vertices));
    vbo_->RegisterBuffer(ntt::LayoutBuffer(ntt::Float2, std::string("position")));
    vbo_->RegisterBuffer(ntt::LayoutBuffer(ntt::Float3, std::string("color")));
    vao_->AppendVertexBuffer(vbo_);

    auto vio_ = std::make_shared<ntt::OpenGLIndexBuffer>(indexes, sizeof(indexes));
    vao_->SetIndexBuffer(vio_);

    triangleVao_ = std::make_shared<ntt::OpenGLVertexArray>();

    auto triangleVbo_ = std::make_shared<ntt::OpenGLVertexBuffer>(triangleVertices, sizeof(triangleVertices));
    triangleVbo_->RegisterBuffer(ntt::LayoutBuffer(ntt::Float2, std::string("position")));
    triangleVbo_->RegisterBuffer(ntt::LayoutBuffer(ntt::Float3, std::string("color")));
    triangleVao_->AppendVertexBuffer(triangleVbo_);

    auto triangleVio_ = std::make_shared<ntt::OpenGLIndexBuffer>(triangleIndexes, sizeof(triangleIndexes));
    triangleVao_->SetIndexBuffer(triangleVio_);

    shader_ = std::make_unique<ntt::Shader>(std::string("../resources/shaders/basic.shader"),
                            std::string("vertex"), std::string("fragment"));
    shader_->UnBind();
}

TestLayer::~TestLayer()
{
    NTT_APPLICATION_INFO("Delete Test Layer");
}

void TestLayer::OnUpdate()
{
    shader_->Bind();
    ntt::RendererAPI::Begin();
    if (visibleVao_)
    {
        ntt::RendererAPI::Submit(vao_);
    }

    if (visibleTriangleVao_)
    {
        ntt::RendererAPI::Submit(triangleVao_);
    }
    ntt::RendererAPI::End();
}

void TestLayer::OnImGuiRenderImpl()
{
    ImGui::Checkbox("Square Vao", &visibleVao_);
    ImGui::Checkbox("Triangle Vao", &visibleTriangleVao_);
}
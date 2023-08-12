#include <GL/glew.h>
#include <glfw/glfw3.h>
#include "TestLayer.hpp"
#include <NTTEngine/NTTEngine.hpp>


TestLayer::TestLayer()
    : Layer("Test Layer"), moveSpeed_(1.0), rotateSpeed_(90)
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
        -0.5f, -0.3f,
         0.5f, -0.4f,
         0.5f,  0.0f,
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
    triangleVao_->AppendVertexBuffer(triangleVbo_);

    auto triangleVio_ = std::make_shared<ntt::OpenGLIndexBuffer>(triangleIndexes, sizeof(triangleIndexes));
    triangleVao_->SetIndexBuffer(triangleVio_);

    camera_ = std::make_shared<ntt::Camera>(glm::vec3(0.0f, 0.0f, 45.0f), 3.14/2);

    shader_ = std::make_shared<ntt::Shader>(std::string("../resources/shaders/basic.shader"),
                            std::string("vertex"), std::string("fragment"));
    triangleShader_ = std::make_shared<ntt::Shader>(std::string("../resources/shaders/basic.shader"),
                            std::string("vertextriangle"), std::string("fragmenttriangle"));
    shader_->UnBind();
}

TestLayer::~TestLayer()
{
    NTT_APPLICATION_INFO("Delete Test Layer");
}

void TestLayer::OnUpdate(ntt::Timestep ts)
{
    if (ntt::WindowInput::IsKeyPressed(NTT_KEY_A))
    {
        camera_->GetCameraPosPointer()[1] += moveSpeed_ * (float)ts;
    }
    if (ntt::WindowInput::IsKeyPressed(NTT_KEY_S))
    {
        camera_->GetCameraPosPointer()[1] -= moveSpeed_ * (float)ts;
    }
    if (ntt::WindowInput::IsKeyPressed(NTT_KEY_R))
    {
        camera_->GetRotationPointer()[2] += rotateSpeed_ * (float)ts;
    }
    if (ntt::WindowInput::IsKeyPressed(NTT_KEY_Q))
    {
        camera_->GetRotationPointer()[2] -= rotateSpeed_ * (float)ts;
    }

    ntt::RendererAPI::Begin(camera_);
    if (visibleVao_)
    {
        ntt::RendererAPI::Submit(vao_, shader_);
    }

    if (visibleTriangleVao_)
    {
        ntt::RendererAPI::Submit(triangleVao_, triangleShader_);
    }
    ntt::RendererAPI::End();
}

void TestLayer::OnImGuiRenderImpl(ntt::Timestep ts)
{
    ImGui::Checkbox("Square Vao", &visibleVao_);
    ImGui::Checkbox("Triangle Vao", &visibleTriangleVao_);

    ImGui::InputFloat3("Camera Position", camera_->GetCameraPosPointer());
    ImGui::InputFloat3("Camera Front", camera_->GetCameraFrontPointer());
    ImGui::InputFloat3("Camera Up", camera_->GetCameraUpPointer());

    ImGui::SliderFloat("Fov", camera_->GetFovPointer(), 0, 3.14);
    ImGui::SliderFloat3("Rotation", camera_->GetRotationPointer(), -180, 180);

    ImGui::SliderFloat("Move Speed", &moveSpeed_, 0, 1);
    ImGui::SliderFloat("Rotate Speed", &rotateSpeed_, 0, 180);
}
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

    storage_ = std::make_unique<ntt::Storage>(std::make_shared<ntt::RealFileSystem>("./test-layer.json"));

    auto camPos = storage_->GetValue<std::vector<float>>("camPos", std::vector<float> {0, 0, 45});
    auto rotation = storage_->GetValue<std::vector<float>>("rotation", std::vector<float> {0, 0, 0});
    auto camFront = storage_->GetValue<std::vector<float>>("camFront", std::vector<float> {0, 0, -1});
    auto camUp = storage_->GetValue<std::vector<float>>("camUp", std::vector<float> {0, 1, 0});

    moveSpeed_ = storage_->GetValue<float>("moveSpeed", 1);
    rotateSpeed_ = storage_->GetValue<float>("rotateSpeed", 90);

    camera_ = std::make_shared<ntt::Camera>(
                        ntt::NTTVec3(camPos), 
                        storage_->GetValue<float>("fov", 1.57),
                        ntt::NTTVec3(rotation),
                        ntt::NTTVec3(camFront),
                        ntt::NTTVec3(camUp));

    shader_ = std::make_shared<ntt::Shader>(std::string("../resources/shaders/basic.shader"),
                            std::string("vertex"), std::string("fragment"));
    triangleShader_ = std::make_shared<ntt::Shader>(std::string("../resources/shaders/basic.shader"),
                            std::string("vertextriangle"), std::string("fragmenttriangle"));
    shader_->UnBind();
}

TestLayer::~TestLayer()
{
    storage_->SetValue<float>("fov", *(camera_->GetFovPointer()));
    storage_->SetValue<float>("moveSpeed", moveSpeed_);
    storage_->SetValue<float>("rotateSpeed", rotateSpeed_);

    storage_->SetValue<std::vector<float>>("camPos", camera_->GetCameraPos().GetVector());

    auto camFront = camera_->GetCameraFront();
    storage_->SetValue<std::vector<float>>("camFront", camera_->GetCameraFront().GetVector());

    auto camUp = camera_->GetCameraUp();
    storage_->SetValue<std::vector<float>>("camUp", camera_->GetCameraUp().GetVector());

    auto rotation = camera_->GetRotation();
    storage_->SetValue<std::vector<float>>("rotation", camera_->GetRotation().GetVector());

    storage_->Save();
}

void TestLayer::OnUpdate(ntt::Timestep ts)
{
    if (ntt::WindowInput::IsKeyPressed(NTT_KEY_A))
    {
        camera_->GetCameraPos().GetGlmVec3().y += moveSpeed_ * (float)ts;
    }
    if (ntt::WindowInput::IsKeyPressed(NTT_KEY_S))
    {
        camera_->GetCameraPos().GetGlmVec3().y -= moveSpeed_ * (float)ts;
    }
    if (ntt::WindowInput::IsKeyPressed(NTT_KEY_R))
    {
        camera_->GetRotation().GetGlmVec3().y += rotateSpeed_ * (float)ts;
    }
    if (ntt::WindowInput::IsKeyPressed(NTT_KEY_Q))
    {
        camera_->GetRotation().GetGlmVec3().y -= rotateSpeed_ * (float)ts;
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

    ImGui::InputFloat3("Camera Position", camera_->GetCameraPos().GetFirstPointer());
    ImGui::InputFloat3("Camera Front", camera_->GetCameraFront().GetFirstPointer());
    ImGui::InputFloat3("Camera Up", camera_->GetCameraUp().GetFirstPointer());

    ImGui::SliderFloat("Fov", camera_->GetFovPointer(), 0, 3.14);
    ImGui::SliderFloat3("Rotation", camera_->GetRotation().GetFirstPointer(), -180, 180);

    ImGui::SliderFloat("Move Speed", &moveSpeed_, 0, 2);
    ImGui::SliderFloat("Rotate Speed", &rotateSpeed_, 0, 180);
}
#include <GL/glew.h>
#include <glfw/glfw3.h>
#include "TestLayer.hpp"
#include <NTTEngine/NTTEngine.hpp>
#include <glm/gtc/matrix_transform.hpp>


TestLayer::TestLayer()
    : Layer("Test Layer"), moveSpeed_(1.0), rotateSpeed_(90)
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
    vbo_->RegisterBuffer(ntt::LayoutBuffer(ntt::Float2, std::string("texture")));
    // vbo_->RegisterBuffer(ntt::LayoutBuffer(ntt::Float3, std::string("color")));
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

    visibleVao_ = storage_->GetValue<bool>("visibleVao", true);
    visibleTriangleVao_ = storage_->GetValue<bool>("visibleTriangleVao", true);
    moveSpeed_ = storage_->GetValue<float>("moveSpeed", 1);
    rotateSpeed_ = storage_->GetValue<float>("rotateSpeed", 90);
    scaled_ = storage_->GetValue<float>("scaled", 1);
    squareDistance_ = storage_->GetValue<float>("squareDistance", 0.2);
    imageScaled_ = storage_->GetValue<float>("imageScaled", 1);

    squareColor_ 
            = std::make_unique<ntt::NTTVec3>(
                storage_->GetValue<std::vector<float>>("squareColor", { 0, 0, 0}));

    camera_ = std::make_shared<ntt::Camera>(
                        ntt::NTTVec3(camPos), 
                        storage_->GetValue<float>("fov", 1.57),
                        ntt::NTTVec3(rotation),
                        ntt::NTTVec3(camFront),
                        ntt::NTTVec3(camUp));

    triangleTransform_ 
        = std::make_unique<ntt::NTTVec3>(
            storage_->GetValue<std::vector<float>>("triangleTransform", { 0, 0, 0 }));

    imageTransform_ 
        = std::make_unique<ntt::NTTVec3>(
            storage_->GetValue<std::vector<float>>("imageTransform", { 0, 0, 0 }));

    shader_ = std::make_shared<ntt::Shader>(std::string("../resources/shaders/basic.shader"),
                            std::string("vertex"), std::string("fragment"));
    triangleShader_ = std::make_shared<ntt::Shader>(std::string("../resources/shaders/basic.shader"),
                            std::string("vertextriangle"), std::string("fragmenttriangle"));
    imageShader_ = std::make_shared<ntt::Shader>(std::string("../resources/shaders/basic.shader"),
                            std::string("vertex"), std::string("image-fragment"));

    // texture_ = std::make_shared<ntt::OpenGLTexture2D>("C:/Users/Acer/Downloads/flower.png");
    // texture_ = std::make_shared<ntt::OpenGLTexture2D>("C:/Users/Acer/Downloads/images.jpg");
    texture_ = std::make_shared<ntt::OpenGLTexture2D>("C:/Users/Acer/OneDrive - Hanoi University of Science and Technology/Pictures/hust.png");
    // texture_ = std::make_shared<ntt::OpenGLTexture2D>("C:/Users/Acer/Downloads/0-0.png");
    texture_->Bind();
    imageShader_->SetUniform1i("m_Texture", 0);
}

TestLayer::~TestLayer()
{
    storage_->SetValue<float>("fov", *(camera_->GetFovPointer()));
    storage_->SetValue<float>("moveSpeed", moveSpeed_);
    storage_->SetValue<float>("rotateSpeed", rotateSpeed_);
    storage_->SetValue<float>("scaled", scaled_);
    storage_->SetValue<float>("imageScaled", imageScaled_);
    storage_->SetValue<float>("squareDistance", squareDistance_);
    storage_->SetValue<bool>("visibleVao", visibleVao_);
    storage_->SetValue<bool>("visibleTriangleVao", visibleTriangleVao_);

    storage_->SetValue<std::vector<float>>("squareColor", squareColor_->GetVector());
    storage_->SetValue<std::vector<float>>("camPos", camera_->GetCameraPos().GetVector());
    storage_->SetValue<std::vector<float>>("triangleTransform", triangleTransform_->GetVector());
    storage_->SetValue<std::vector<float>>("imageTransform", imageTransform_->GetVector());

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
        for (int i=0; i<10; i++)
        {
            for (int j=0; j<10; j++)
            {
                glm::vec3 pos = glm::vec3(
                                triangleTransform_->GetGlmVec3().x + squareDistance_ * j,
                                triangleTransform_->GetGlmVec3().y + squareDistance_ * i,
                                triangleTransform_->GetGlmVec3().z);
                glm::mat4 transformMatrix = glm::translate(glm::mat4(1.0f), pos);
                glm::mat4 scaledMatrix = glm::scale(transformMatrix, glm::vec3(scaled_));
                shader_->SetUniform3f("m_Color", squareColor_->GetGlmVec3());
                ntt::RendererAPI::Submit(vao_, shader_, scaledMatrix);
            }
        }

        glm::mat4 transformMatrix = glm::translate(glm::mat4(1.0f), imageTransform_->GetGlmVec3());
        glm::mat4 scaledMatrix = glm::scale(transformMatrix, glm::vec3(imageScaled_));
        ntt::RendererAPI::Submit(vao_, imageShader_, scaledMatrix);
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

    ImGui::SliderFloat("Camera Fov", camera_->GetFovPointer(), 0, 3.14);
    ImGui::SliderFloat3("Camera Rotation", camera_->GetRotation().GetFirstPointer(), -180, 180);

    ImGui::SliderFloat("Camera Move Speed", &moveSpeed_, 0, 2);
    ImGui::SliderFloat("Camera Rotate Speed", &rotateSpeed_, 0, 180);

    ImGui::SliderFloat3("Squared Transform", triangleTransform_->GetFirstPointer(), -2, 2);
    ImGui::SliderFloat("Squared Scaled", &scaled_, 0, 1);
    ImGui::SliderFloat("Squared Distance", &squareDistance_, -1, 1);

    ImGui::SliderFloat3("Image Transform", imageTransform_->GetFirstPointer(), -3, 3);
    ImGui::SliderFloat("Image Scaled", &imageScaled_, 0, 2);

    ImGui::ColorPicker3("Squared Color", squareColor_->GetFirstPointer());
}
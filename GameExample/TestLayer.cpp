#include <GL/glew.h>
#include <glfw/glfw3.h>
#include "TestLayer.hpp"
#include <NTTEngine/NTTEngine.hpp>
#include <glm/gtc/matrix_transform.hpp>


TestLayer::TestLayer(std::shared_ptr<ntt::ICamera> camera)
    : Layer("Test Layer"), camera_(camera)
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

    vao_ = std::make_shared<ntt::VertexArray>();

    auto vbo_ = std::make_shared<ntt::VertexBuffer>(vertices, sizeof(vertices));
    vbo_->RegisterBuffer(ntt::LayoutBuffer(ntt::Float2, std::string("position")));
    vbo_->RegisterBuffer(ntt::LayoutBuffer(ntt::Float2, std::string("texture")));
    // vbo_->RegisterBuffer(ntt::LayoutBuffer(ntt::Float3, std::string("color")));
    vao_->AppendVertexBuffer(vbo_);

    auto vio_ = std::make_shared<ntt::IndexBuffer>(indexes, sizeof(indexes));
    vao_->SetIndexBuffer(vio_);

    triangleVao_ = std::make_shared<ntt::VertexArray>();

    auto triangleVbo_ = std::make_shared<ntt::VertexBuffer>(triangleVertices, sizeof(triangleVertices));
    triangleVbo_->RegisterBuffer(ntt::LayoutBuffer(ntt::Float2, std::string("position")));
    triangleVao_->AppendVertexBuffer(triangleVbo_);

    auto triangleVio_ = std::make_shared<ntt::IndexBuffer>(triangleIndexes, sizeof(triangleIndexes));
    triangleVao_->SetIndexBuffer(triangleVio_);

    storage_ = std::make_unique<ntt::Storage>(std::make_shared<ntt::RealFileSystem>("./test-layer.json"));

    visibleVao_ = storage_->GetValue<bool>("visibleVao", true);
    visibleTriangleVao_ = storage_->GetValue<bool>("visibleTriangleVao", true);
    scaled_ = storage_->GetValue<float>("scaled", 1);
    squareDistance_ = storage_->GetValue<float>("squareDistance", 0.2);
    imageScaled_ = storage_->GetValue<float>("imageScaled", 1);

    squareColor_ 
            = std::make_unique<ntt::NTTVec3>(
                storage_->GetValue<std::vector<float>>("squareColor", { 0, 0, 0}));

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

    texture_ = std::make_shared<ntt::Texture2D>("C:/Users/Acer/Downloads/images.jpg");
    texture_->Bind();
    imageShader_->SetUniform1i("m_Texture", 0);
}

TestLayer::~TestLayer()
{
    NTT_APPLICATION_DEBUG("Start Delete Test Layer");
    storage_->SetValue<float>("scaled", scaled_);
    storage_->SetValue<float>("imageScaled", imageScaled_);
    storage_->SetValue<float>("squareDistance", squareDistance_);
    storage_->SetValue<bool>("visibleVao", visibleVao_);
    storage_->SetValue<bool>("visibleTriangleVao", visibleTriangleVao_);

    storage_->SetValue<std::vector<float>>("imageTransform", imageTransform_->GetVector());

    storage_->Save();
    NTT_APPLICATION_DEBUG("Finish Delete Test Layer");
}

void TestLayer::OnUpdate(ntt::Timestep ts)
{
    ntt::RendererAPI::Begin(camera_, ts);
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

    ImGui::SliderFloat3("Squared Transform", triangleTransform_->GetFirstPointer(), -2, 2);
    ImGui::SliderFloat("Squared Scaled", &scaled_, 0, 1);
    ImGui::SliderFloat("Squared Distance", &squareDistance_, -1, 1);

    ImGui::SliderFloat3("Image Transform", imageTransform_->GetFirstPointer(), -3, 3);
    ImGui::SliderFloat("Image Scaled", &imageScaled_, 0, 2);

    ImGui::ColorPicker3("Squared Color", squareColor_->GetFirstPointer());

    camera_->OnImGuiRender(ts);
}


void TestLayer::OnWindowResize(ntt::WindowResizeEvent& event)
{

}
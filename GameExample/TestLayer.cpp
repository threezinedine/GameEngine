#include <GL/glew.h>
#include <glfw/glfw3.h>
#include "TestLayer.hpp"
#include <NTTEngine/NTTEngine.hpp>
#include <glm/gtc/matrix_transform.hpp>


TestLayer::TestLayer(std::shared_ptr<ntt::Camera> camera)
    : Layer("Test Layer"), camera_(camera)
{
    PROFILE_SCOPE();
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
    vao_->AppendVertexBuffer(vbo_);

    auto vio_ = std::make_shared<ntt::IndexBuffer>(indexes, sizeof(indexes));
    vao_->SetIndexBuffer(vio_);

    triangleVao_ = std::make_shared<ntt::VertexArray>();

    auto triangleVbo_ = std::make_shared<ntt::VertexBuffer>(triangleVertices, sizeof(triangleVertices));
    triangleVbo_->RegisterBuffer(ntt::LayoutBuffer(ntt::Float2, std::string("position")));
    triangleVao_->AppendVertexBuffer(triangleVbo_);

    auto triangleVio_ = std::make_shared<ntt::IndexBuffer>(triangleIndexes, sizeof(triangleIndexes));
    triangleVao_->SetIndexBuffer(triangleVio_);

    storage_ = std::make_shared<ntt::Storage>(
        std::make_shared<ntt::RealFileSystem>("./test-layer.json"));

    visibleVao_ = std::make_unique<ntt::ThreadValue<bool>>(true, storage_, "visibleVao");
    visibleTriangleVao_ = std::make_unique<ntt::ThreadValue<bool>>(true, storage_, "visibleTriangle");
    scaled_ = std::make_unique<ntt::ThreadValue<float>>(1, 0, 2, storage_, "scaled");
    squareDistance_ = 
            std::make_unique<ntt::ThreadValue<float>>(0.2, 0, 1, storage_, "squareDistance");
    imageScaled_ = 
            std::make_unique<ntt::ThreadValue<float>>(1, 0.5, 2, storage_, "imageScaled");

    squareColor_ = 
        std::make_unique<ntt::NTTVec3>(
            std::vector<float>{0, 0, 0}, storage_, "squareColor"
        );

    triangleTransform_ = 
        std::make_unique<ntt::NTTVec3>(
            std::vector<float>{0, 0, 0}, storage_, "squareTransform"
        );

    imageTransform_ = 
        std::make_unique<ntt::NTTVec3>(
            std::vector<float>{0, 0, 0}, storage_, "imageTransform"
        );

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
    PROFILE_SCOPE();
    scaled_->Save();
    imageScaled_->Save();
    squareDistance_->Save();
    visibleVao_->Save();
    visibleTriangleVao_->Save();

    squareColor_->Save();
    triangleTransform_->Save();
    imageTransform_->Save();

    storage_->Save();
}

void TestLayer::OnUpdate(ntt::Timestep ts)
{
    PROFILE_SCOPE();
    ntt::RendererAPI::Begin(camera_, ts);
    if (visibleVao_->GetValue())
    {
        for (int i=0; i<10; i++)
        {
            for (int j=0; j<10; j++)
            {
                glm::vec3 pos = glm::vec3(
                                triangleTransform_->GetGlmVec3().x + squareDistance_->GetValue() * j,
                                triangleTransform_->GetGlmVec3().y + squareDistance_->GetValue() * i,
                                triangleTransform_->GetGlmVec3().z);
                glm::mat4 transformMatrix = glm::translate(glm::mat4(1.0f), pos);
                glm::mat4 scaledMatrix = glm::scale(transformMatrix, glm::vec3(scaled_->GetValue()));
                shader_->SetUniform3f("m_Color", squareColor_->GetGlmVec3());
                ntt::RendererAPI::Submit(vao_, shader_, scaledMatrix);
            }
        }

        glm::mat4 transformMatrix = glm::translate(glm::mat4(1.0f), imageTransform_->GetGlmVec3());
        glm::mat4 scaledMatrix = glm::scale(transformMatrix, glm::vec3(imageScaled_->GetValue()));
        ntt::RendererAPI::Submit(vao_, imageShader_, scaledMatrix);
    }

    if (visibleTriangleVao_->GetValue())
    {
        ntt::RendererAPI::Submit(triangleVao_, triangleShader_);
    }
    ntt::RendererAPI::End();
}

void TestLayer::OnImGuiRenderImpl(ntt::Timestep ts)
{
    PROFILE_SCOPE();

    ImGui::Checkbox("Square Vao", visibleVao_->GetPointer());
    ImGui::Checkbox("Triangle Vao", visibleTriangleVao_->GetPointer());

    ImGui::SliderFloat3("Squared Transform", triangleTransform_->GetFirstPointer(), -2, 2);
    ImGui::SliderFloat("Squared Scaled", scaled_->GetPointer(), 0, 1);
    ImGui::SliderFloat("Squared Distance", squareDistance_->GetPointer(), -1, 1);

    ImGui::SliderFloat3("Image Transform", imageTransform_->GetFirstPointer(), -3, 3);
    ImGui::SliderFloat("Image Scaled", imageScaled_->GetPointer(), 0, 2);

    ImGui::ColorPicker3("Squared Color", squareColor_->GetFirstPointer());

    camera_->OnImGuiRender(ts);
}


void TestLayer::OnWindowResize(ntt::WindowResizeEvent& event)
{

}
#include <GL/glew.h>
#include <glfw/glfw3.h>
#include "TestLayer.hpp"
#include <NTTEngine/NTTEngine.hpp>


TestLayer::TestLayer()
    : Layer("Test Layer")
{
    vao_ = std::make_unique<ntt::OpenGLVertexArray>();

    float vertices[] = 
    {
        -0.5f, -0.5f, 1.0f, 1.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
         0.5f,  0.5f, 1.0f, 1.0f, 0.0f,
    };

    vbo_ = std::make_unique<ntt::OpenGLVertexBuffer>(vertices, sizeof(vertices));

    vbo_->RegisterBuffer(ntt::LayoutBuffer(ntt::Float2, std::string("position")));
    vbo_->RegisterBuffer(ntt::LayoutBuffer(ntt::Float3, std::string("color")));
    vbo_->Setup();

    unsigned int indexes[] = 
    { 
        0, 1, 2, 
        1, 2, 3,
    };

    vio_ = std::make_unique<ntt::OpenGLIndexBuffer>(indexes, sizeof(indexes));
}

TestLayer::~TestLayer()
{
    NTT_APPLICATION_INFO("Delete Test Layer");
}

void TestLayer::OnUpdate()
{
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
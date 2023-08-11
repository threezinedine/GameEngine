#include <GL/glew.h>
#include <glfw/glfw3.h>
#include "TestLayer.hpp"
#include <NTTEngine/NTTEngine.hpp>


TestLayer::TestLayer()
    : Layer("Test Layer")
{
    vao_ = std::make_unique<ntt::OpenGLVertexArray>();
    // NTT_APPLICATION_DEBUG("vao value: {}", vao_);
    // glGenVertexArrays(1, &vao_);
    // NTT_APPLICATION_DEBUG("vao value: {}", vao_);
    // glBindVertexArray(vao_);

    float vertices[] = 
    {
        -0.5f, -0.5f,
         0.5f, -0.5f,
        -0.5f,  0.5f,
         0.5f,  0.5f,
    };

    vbo_ = std::make_unique<ntt::OpenGLVertexBuffer>(vertices, sizeof(vertices));
    // NTT_APPLICATION_DEBUG("vbo value: {}", vbo_);
    // glGenBuffers(1, &vbo_);
    // NTT_APPLICATION_DEBUG("vbo value: {}", vbo_);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), nullptr);

    unsigned int indexes[] = 
    { 
        0, 1, 2, 
        1, 2, 3,
    };
    // glGenBuffers(1, &vio_);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vio_);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

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
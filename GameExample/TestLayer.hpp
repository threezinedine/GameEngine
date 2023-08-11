#pragma once
#include <memory>
#include <NTTEngine/NTTEngine.hpp>

class TestLayer: public ntt::Layer
{
    public:
        TestLayer();
        ~TestLayer();

        void OnUpdate() override;

    private:
        std::unique_ptr<ntt::VertexArray> vao_;
        std::unique_ptr<ntt::VertexBuffer> vbo_;
        std::unique_ptr<ntt::IndexBuffer> vio_;
};
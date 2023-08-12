#pragma once
#include <memory>
#include <NTTEngine/NTTEngine.hpp>

class TestLayer: public ntt::Layer
{
    public:
        TestLayer();
        ~TestLayer();

        void OnUpdate(ntt::Timestep ts) override;
        void OnImGuiRenderImpl(ntt::Timestep ts) override;

    private:
        std::shared_ptr<ntt::VertexArray> vao_;
        std::shared_ptr<ntt::VertexArray> triangleVao_;
        std::shared_ptr<ntt::Shader> shader_;
        std::shared_ptr<ntt::Shader> triangleShader_;

        std::shared_ptr<ntt::Camera> camera_;

        bool visibleVao_ = true;
        bool visibleTriangleVao_ = true;

        float moveSpeed_;
        float rotateSpeed_;
};
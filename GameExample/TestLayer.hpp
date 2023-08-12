#pragma once
#include <memory>
#include <NTTEngine/NTTEngine.hpp>

class TestLayer: public ntt::Layer
{
    public:
        TestLayer();
        ~TestLayer();

        void OnUpdate() override;
        void OnImGuiRenderImpl() override;

    private:
        std::unique_ptr<ntt::VertexArray> vao_;
        std::unique_ptr<ntt::VertexArray> triangleVao_;

        bool visibleVao_ = true;
        bool visibleTriangleVao_ = true;
};
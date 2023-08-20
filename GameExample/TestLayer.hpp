#pragma once
#include <memory>
#include "Storage.hpp"
#include <NTTEngine/NTTEngine.hpp>

class TestLayer: public ntt::Layer
{
    public:
        TestLayer(std::shared_ptr<ntt::ICamera> camera);
        ~TestLayer();

        void OnUpdate(ntt::Timestep ts) override;
        void OnImGuiRenderImpl(ntt::Timestep ts) override;

        void OnWindowResize(ntt::WindowResizeEvent& event) override;

    private:
        std::shared_ptr<ntt::Texture2D> texture_;
        std::shared_ptr<ntt::VertexArray> vao_;
        std::shared_ptr<ntt::VertexArray> triangleVao_;
        std::shared_ptr<ntt::Shader> shader_;
        std::shared_ptr<ntt::Shader> imageShader_;
        std::shared_ptr<ntt::Shader> triangleShader_;

        std::shared_ptr<ntt::ICamera> camera_;

        std::unique_ptr<ntt::ThreadValue<bool>> visibleVao_;
        std::unique_ptr<ntt::ThreadValue<bool>> visibleTriangleVao_;

        std::unique_ptr<ntt::ThreadValue<float>> scaled_;
        std::unique_ptr<ntt::ThreadValue<float>> imageScaled_;
        std::unique_ptr<ntt::ThreadValue<float>> squareDistance_;

        std::unique_ptr<ntt::NTTVec3> squareColor_;
        std::unique_ptr<ntt::NTTVec3> triangleTransform_;
        std::unique_ptr<ntt::NTTVec3> imageTransform_;

        std::shared_ptr<ntt::Storage> storage_;
};
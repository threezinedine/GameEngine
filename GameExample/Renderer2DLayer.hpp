#pragma once
#include "Storage.hpp"
#include "NTTEngine/NTTEngine.hpp"


class Renderer2DLayer: public ntt::Layer
{
    public:
        Renderer2DLayer(std::shared_ptr<ntt::Camera>& camera);
        ~Renderer2DLayer();
        // virtual void OnAttach() override;
        // virtual void OnDetach() override;
        virtual void OnUpdate(ntt::Timestep ts) override;

        void OnImGuiRenderImpl(ntt::Timestep ts) override;
    private:
        std::shared_ptr<ntt::Shader> shader_;
        std::shared_ptr<ntt::VertexArray> vao_;
        std::shared_ptr<ntt::Camera>& camera_;

        std::unique_ptr<ntt::NTTVec3> squareColor_;
        std::shared_ptr<ntt::Storage> storage_;
};
#pragma once
#include "NTTEngine/NTTEngine.hpp"


class GameExampleLayer: public ntt::Layer
{
    public:
        GameExampleLayer(std::shared_ptr<ntt::Camera>& camera);
        ~GameExampleLayer();

        void OnAttach() override;
        void OnUpdate(ntt::Timestep ts) override;
        void OnImGuiRenderImpl(ntt::Timestep ts) override;       

    private:
        std::shared_ptr<ntt::Camera>& camera_;
        std::shared_ptr<ntt::Texture2D> map_;
        std::shared_ptr<ntt::SubTexture2D> plane_;
        std::shared_ptr<ntt::TextureMap> textureMap_;
        std::shared_ptr<ntt::FrameBuffer> frameBuffer_;
};
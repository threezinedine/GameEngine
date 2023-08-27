#include "GameExampleLayer.hpp"


GameExampleLayer::GameExampleLayer(std::shared_ptr<ntt::Camera>& camera)
    : ntt::Layer("GameExampleLayer"), camera_(camera)
{
}

GameExampleLayer::~GameExampleLayer()
{

}

void GameExampleLayer::OnAttach()
{
    map_ = std::make_shared<ntt::Texture2D>(
        "C:/Users/Acer/C_Language/C++/GameEngine/GameExample/assets/Tilemap/tilemap_packed.png",
        18, 11, 33
    );

    plane_ = std::make_shared<ntt::SubTexture2D>
    (
        map_, 10, 1, 33
    );

    textureMap_ = std::make_shared<ntt::TextureMap>(
        "texture-map",
        map_, 18, 11, 33
    );
}

void GameExampleLayer::OnUpdate(ntt::Timestep ts)
{
    ntt::Renderer2D::BeginScene(camera_, ts);

    textureMap_->OnUpdate(ts);

    ntt::Renderer2D::EndScene();
}

void GameExampleLayer::OnImGuiRenderImpl(ntt::Timestep ts)
{
    textureMap_->OnImGuiRender(ts);
}
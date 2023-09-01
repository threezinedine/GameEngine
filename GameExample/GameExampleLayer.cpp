#include "GameExampleLayer.hpp"
#include <glm/gtx/string_cast.hpp>


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

    frameBuffer_ = std::make_shared<ntt::FrameBuffer>(ntt::Window::GetInstance()->GetWidth(), 
                                                        ntt::Window::GetInstance()->GetHeight());
}

void GameExampleLayer::OnUpdate(ntt::Timestep ts)
{
    // frameBuffer_->Bind();
    ntt::Renderer2D::Clear();
    ntt::Renderer2D::BeginScene(camera_, ts);

    // ntt::Renderer2D::DrawQuad( { 0, 0, 0 }, { 1, 1 }, map_ );
    textureMap_->OnUpdate(ts);

    ntt::Renderer2D::EndScene();
    // frameBuffer_->UnBind();
}

void GameExampleLayer::OnImGuiRenderImpl(ntt::Timestep ts)
{
    textureMap_->OnImGuiRender(ts);
    camera_->OnImGuiRender(ts);
    ImGui::Image((ImTextureID)frameBuffer_->GetColorTextureId(), { 720, 480 });
}
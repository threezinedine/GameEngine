#include <memory>
#include "Renderer2DLayer.hpp"


Renderer2DLayer::Renderer2DLayer(std::shared_ptr<ntt::Camera>& camera)
    : Layer("2DRendererLayer"), camera_(camera)
{
    PROFILE_SCOPE();

    storage_ = std::make_shared<ntt::Storage>(
        std::make_shared<ntt::RealFileSystem>("./" + GetName() + "-layer.json"));

    squareColor_ = 
        std::make_unique<ntt::NTTVec3>(
            std::vector<float>{0, 0, 0}, storage_, "squareColor"
        );

    texture_ = std::make_shared<ntt::Texture2D>(
        "C:/Users/Acer/Downloads/images.jpg"
    );
}

Renderer2DLayer::~Renderer2DLayer()
{
    PROFILE_SCOPE();

    squareColor_->Save(); 
    storage_->Save();
}

void Renderer2DLayer::OnUpdate(ntt::Timestep ts)
{
    PROFILE_SCOPE();

    ntt::Renderer2D::BeginScence(camera_, ts);

    ntt::Renderer2D::DrawQuad({ 0, 0 }, { 0.5, 0.5 }, squareColor_->GetGlmVec3());
    ntt::Renderer2D::DrawQuad({ 3, 0.3 }, { 1, 1 }, squareColor_->GetGlmVec3());
    ntt::Renderer2D::DrawQuad({ 1, 1, -0.1 }, { 2, 2 }, texture_);

    ntt::Renderer2D::End();
}


void Renderer2DLayer::OnImGuiRenderImpl(ntt::Timestep ts)
{
    PROFILE_SCOPE();

    ImGui::ColorPicker3("Squared Color", squareColor_->GetFirstPointer());
    camera_->OnImGuiRender(ts);
}

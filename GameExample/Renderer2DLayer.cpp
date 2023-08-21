#include <memory>
#include "Renderer2DLayer.hpp"


Renderer2DLayer::Renderer2DLayer(std::shared_ptr<ntt::Camera>& camera)
    : Layer("2DRendererLayer"), camera_(camera)
{
    storage_ = std::make_shared<ntt::Storage>(
        std::make_shared<ntt::RealFileSystem>("./" + GetName() + "-layer.json"));

    squareColor_ = 
        std::make_unique<ntt::NTTVec3>(
            std::vector<float>{0, 0, 0}, storage_, "squareColor"
        );
}

Renderer2DLayer::~Renderer2DLayer()
{
    squareColor_->Save(); 
    storage_->Save();
}

void Renderer2DLayer::OnUpdate(ntt::Timestep ts)
{
    ntt::Renderer2D::BeginScence(camera_, ts);

    ntt::Renderer2D::DrawQuad(glm::vec2(0, 0), glm::vec2(10, 10), squareColor_->GetGlmVec3());

    ntt::Renderer2D::End();
}


void Renderer2DLayer::OnImGuiRenderImpl(ntt::Timestep ts)
{
    ImGui::ColorPicker3("Squared Color", squareColor_->GetFirstPointer());
    camera_->OnImGuiRender(ts);
}

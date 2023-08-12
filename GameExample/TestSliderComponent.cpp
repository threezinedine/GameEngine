#include <imgui.h>
#include <NTTEngine/NTTEngine.hpp>
#include "TestSliderComponent.hpp"


TestSliderComponent::TestSliderComponent()
    : ntt::ImGuiComponent("Test Slider"), value_(0)
{

}

TestSliderComponent::~TestSliderComponent()
{
    NTT_APPLICATION_DEBUG("Delete Test Slider component");
}

void TestSliderComponent::OnImGuiRender(ntt::Timestep ts)
{
    ImGui::SliderFloat("Test Slider", &value_, 0.0f, 1.0f);
}
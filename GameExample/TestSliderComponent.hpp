#pragma once 
#include <string>
#include <NTTEngine/NTTEngine.hpp>


class TestSliderComponent: public ntt::ImGuiComponent
{
    public:
        TestSliderComponent();
        ~TestSliderComponent();

        void OnImGuiRender(ntt::Timestep ts) override;

    private:
        float value_;
};
#pragma once
#include "NTTEngine/NTTEngine.hpp"


class ESP32ImGuiApplication: public ntt::ImGuiApplication
{
    public:
        ESP32ImGuiApplication();
        ~ESP32ImGuiApplication();

        void OnImGuiRenderImpl(ntt::Timestep ts) override;
    private:

};

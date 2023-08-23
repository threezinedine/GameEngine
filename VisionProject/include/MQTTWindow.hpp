#pragma once
#include <NTTEngine/NTTEngine.hpp>


class MQTTWindow: public ntt::ImGuiApplication
{
    public:
        MQTTWindow();
        ~MQTTWindow();

        void OnImGuiRenderImpl(ntt::Timestep ts) override;

        static float temperatureValue;
    private:
};
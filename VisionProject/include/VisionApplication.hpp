#pragma once

#include <NTTEngine/NTTEngine.hpp>
#include <Webcam.hpp>
#include <MQTT/MQTT.hpp>
#include "ImageProcessing/ImageProcessing.hpp"


class VisionApplication: public ntt::Application
{
    public:
        VisionApplication(); 
        ~VisionApplication();

        void OnSetupImpl() override;
        void OnUpdateImpl(ntt::Timestep ts) override;

        void OnWindowCloseImpl(ntt::WindowCloseEvent& event) override;

    private:
        WebCam webcam_;
        MQTTClient client_;
};
#pragma once
#include <NTTEngine/NTTEngine.hpp>
#include <opencv2/opencv.hpp>
#include <chrono>


class ImageDisplay: public ntt::ImGuiApplication
{
    public:
        ImageDisplay();
        ~ImageDisplay();

        void OnImGuiRenderImpl(ntt::Timestep ts) override;

    private:
        ntt::ImGuiImage image_;
        ntt::TimePlan imageTimePlan_;
        cv::Mat imageData_;
};
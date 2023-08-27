#pragma once
#include <memory>
#include "ImageProcessingStep.hpp"


class ExtractByColor: public ImageProcessingStep
{
    public:
        ExtractByColor();
        ~ExtractByColor();

        cv::Mat OnProcessImpl(cv::Mat image, ImageProcessingContainer* container) override;

        void OnImGuiRenderImpl(ntt::Timestep ts) override;

    private:
        // std::unique_ptr<ntt::ThreadArray<float>> lowerLimitRGB_;
        std::unique_ptr<ntt::ThreadValue<int>> hChannelRange_;
        std::unique_ptr<ntt::ThreadValue<int>> sChannelLowLimitValue_;
        std::unique_ptr<ntt::ThreadValue<int>> vChannelLowLimtValue_;
        std::unique_ptr<ntt::ThreadValue<int>> sChannelUpLimitValue_;
        std::unique_ptr<ntt::ThreadValue<int>> vChannelUpLimtValue_;

        std::unique_ptr<ntt::ThreadArray<float>> detectedColor_;
        std::unique_ptr<ntt::ThreadValue<int>> area_;
};
#pragma once
#include <memory>
#include "Storage.hpp"
#include "ImageProcessingStep.hpp"

class ImageProcessingContainer;

class ExtractByColor: public ImageProcessingStep
{
    public:
        ExtractByColor();
        ~ExtractByColor();

        cv::Mat OnProcessImpl(cv::Mat image, ImageProcessingContainer* container) override;

        void OnImGuiRenderImpl(ntt::Timestep ts) override;

    private:
        std::unique_ptr<ntt::ThreadArray<float>> lowerLimitRGB_;
        std::unique_ptr<ntt::ThreadArray<float>> upperLimitRGB_;
        std::unique_ptr<ntt::ThreadValue<int>> area_;
};
#pragma once

#include "ImageProcessingStep.hpp"


class ExtractCircularObject: public ImageProcessingStep
{
    public:
        ExtractCircularObject();
        ~ExtractCircularObject();

        cv::Mat OnProcessImpl(cv::Mat image, ImageProcessingContainer* container);

        void OnImGuiRenderImpl(ntt::Timestep ts) override;

    private:
        std::unique_ptr<ntt::ThreadValue<int>> method_;
        std::unique_ptr<ntt::ThreadValue<float>> dp_;
        std::unique_ptr<ntt::ThreadValue<float>> minDist_;
        std::unique_ptr<ntt::ThreadValue<float>> param1_;
        std::unique_ptr<ntt::ThreadValue<float>> param2_;
        std::unique_ptr<ntt::ThreadValue<int>> minRadius_;
        std::unique_ptr<ntt::ThreadValue<int>> maxRadius_;
};
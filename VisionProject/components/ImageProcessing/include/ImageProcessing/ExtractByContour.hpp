#pragma once

#include "ImageProcessingStep.hpp"


class ExtractByContour: public ImageProcessingStep
{
    public:
        ExtractByContour();
        ~ExtractByContour();

        cv::Mat OnProcessImpl(cv::Mat image, ImageProcessingContainer* container) override;

        void OnImGuiRenderImpl(ntt::Timestep ts) override;

    private:
        std::unique_ptr<ntt::ThreadValue<bool>> useMinArea_;
        std::unique_ptr<ntt::ThreadValue<int>> area_;
        std::unique_ptr<ntt::ThreadValue<int>> minArea_;
        std::unique_ptr<ntt::ThreadValue<int>> maxArea_;

        bool IsValidArea(double area);
}; 

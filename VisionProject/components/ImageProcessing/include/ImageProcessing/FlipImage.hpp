#pragma once
#include <string>
#include <memory>
#include <opencv2/opencv.hpp>
#include "ImageProcessingStep.hpp"


class FlipImage: public ImageProcessingStep
{
    public:
        FlipImage();
        virtual ~FlipImage();

        cv::Mat OnProcessImpl(cv::Mat image, ImageProcessingContainer* container) override;

        void OnImGuiRenderImpl(ntt::Timestep ts) override;

    private:
};
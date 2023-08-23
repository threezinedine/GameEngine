#pragma once

#include "ImageProcessingStep.hpp"
#include <opencv2/opencv.hpp>

class ImageProcessingContainer;

class ImageCutting: public ImageProcessingStep
{
    public:
        ImageCutting(int imageWidth, int imageHeight);
        ~ImageCutting();

        cv::Mat OnProcessImpl(cv::Mat image, ImageProcessingContainer* container) override;
        void OnImGuiRender(ntt::Timestep ts) override;

    private:
        ntt::ThreadArray<int> topLeftPoint_;
        ntt::ThreadArray<int> rightButtomPoint_;
        int imageWidth_;
        int imageHeight_;
};
#pragma once
#include "ImageProcessingStep.hpp"


class ImageResize: public ImageProcessingStep
{
    public:
        ImageResize(int width);
        ~ImageResize();

        cv::Mat OnProcessImpl(cv::Mat image, ImageProcessingContainer* container) override;

    private:
        int width_;
        int height_;
};
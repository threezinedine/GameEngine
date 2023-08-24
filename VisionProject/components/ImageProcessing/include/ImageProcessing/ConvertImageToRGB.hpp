#pragma once
#include "ImageProcessingStep.hpp"


class ConvertImageToRGB: public ImageProcessingStep
{
    public:
        ConvertImageToRGB();
        ~ConvertImageToRGB();

        cv::Mat OnProcessImpl(cv::Mat mat, ImageProcessingContainer* container) override;
};
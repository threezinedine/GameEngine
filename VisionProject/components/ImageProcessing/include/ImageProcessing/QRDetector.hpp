#pragma once
#include <memory>
#include "ImageProcessingStep.hpp"


class QRDetect: public ImageProcessingStep
{
    public:
        QRDetect();
        ~QRDetect();

        cv::Mat OnProcessImpl(cv::Mat image, ImageProcessingContainer* container) override;

        void OnImGuiRenderImpl(ntt::Timestep ts) override;

    private:
};
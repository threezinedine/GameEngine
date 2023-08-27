#pragma once
#include <memory>
#include "ImageProcessingStep.hpp"


class PnPAlgorithm: public ImageProcessingStep
{
    public:
        PnPAlgorithm();
        ~PnPAlgorithm();

        cv::Mat OnProcessImpl(cv::Mat image, ImageProcessingContainer* container) override;

        void OnImGuiRenderImpl(ntt::Timestep ts) override;

    private:
};
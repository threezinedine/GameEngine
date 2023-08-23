#pragma once
#include <memory>
#include "ImageProcessingStep.hpp"
#include <mutex>
#include "Storage.hpp"


class ImageProcessingContainer;

class ConvertToBinary: public ImageProcessingStep
{
    public:
        ConvertToBinary();
        ~ConvertToBinary();

        cv::Mat OnProcessImpl(cv::Mat image, ImageProcessingContainer* container); 

        void OnImGuiRenderImpl(ntt::Timestep ts) override;

    private:
        std::unique_ptr<ntt::ThreadValue<int>> convertMethod_;

        std::unique_ptr<ntt::ThreadValue<int>> threshold_;
        std::unique_ptr<ntt::ThreadValue<bool>> useAdaptiveThreshold_;
        std::unique_ptr<ntt::ThreadValue<int>> adaptiveNeighborSize_;
        std::unique_ptr<ntt::ThreadValue<int>> adpativeConstantSubtracted_;
        std::unique_ptr<ntt::ThreadValue<int>> adaptiveMethod_;
};
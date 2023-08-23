#pragma once
#include <mutex>
#include <string>
#include <opencv2/opencv.hpp>
#include "NTTEngineThreadSystem/NTTEngineThreadSystem.hpp"
#include "NTTEngineImGuiTools/NTTEngineImGuiTools.hpp"
#include "NTTEngineImGuiLayerSystem/NTTEngineImGuiLayerSystem.hpp"
#include "Storage.hpp"

class ImageProcessingContainer;

class ImageProcessingStep: public ntt::ImGuiComponent
{
    public:
        ImageProcessingStep(const std::string& stepName);
        ~ImageProcessingStep() override;

        cv::Mat OnProcess(cv::Mat mat, ImageProcessingContainer* container);
        virtual cv::Mat OnProcessImpl(cv::Mat image, ImageProcessingContainer* container) = 0;

        void OnImGuiRender(ntt::Timestep ts) override;
        virtual void OnImGuiRenderImpl(ntt::Timestep ts);

    protected:
        std::mutex mutex_;
        cv::Mat image_;
        ntt::ImGuiImage imageContext_;
        std::shared_ptr<ntt::Storage> storage_;

        cv::Mat VerifyImage(cv::Mat image);

        std::unique_ptr<ntt::ThreadValue<bool>> isUsed_;
        std::unique_ptr<ntt::ThreadValue<bool>> openTree_;
        std::shared_ptr<ntt::ThreadValue<bool>> displayImage_;
};
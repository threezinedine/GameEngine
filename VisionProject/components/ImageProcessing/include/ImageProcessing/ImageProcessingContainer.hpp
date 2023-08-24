#pragma once
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <opencv2/opencv.hpp>
#include "NTTEngineImGuiLayerSystem/ImGuiApplication.hpp"

class ImageProcessingStep;

class ImageProcessingContainer: public ntt::ImGuiApplication
{
    public:
        ImageProcessingContainer();
        virtual ~ImageProcessingContainer();

        cv::Mat OnProcess(cv::Mat image);
        void AppendStep(std::shared_ptr<ImageProcessingStep> step);
        void PopStep(std::shared_ptr<ImageProcessingStep> step);

        void OnImGuiRenderImpl(ntt::Timestep ts) override;

        inline const cv::Mat& GetOriginalImage() const { return originalImage_; }
        inline void SetOriginalImage(const cv::Mat& image) { originalImage_ = image; }

    private:
        cv::Mat originalImage_;
        std::vector<std::shared_ptr<ImageProcessingStep>> steps_;
        int index_ = 0;
};
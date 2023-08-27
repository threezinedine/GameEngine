#pragma once
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <opencv2/opencv.hpp>
#include <glm/glm.hpp>
#include "NTTEngineImGuiLayerSystem/ImGuiApplication.hpp"

struct CoordVertex
{
    glm::vec2 realWorldPos;
    glm::vec2 imagePos;
    bool isFixed;
};

class ImageProcessingStep;

class ImageProcessingContainer: public ntt::ImGuiApplication
{
    public:
        ImageProcessingContainer(int minVertexes = 5);
        virtual ~ImageProcessingContainer();

        cv::Mat OnProcess(cv::Mat image);
        void AppendStep(std::shared_ptr<ImageProcessingStep> step);
        void PopStep(std::shared_ptr<ImageProcessingStep> step);

        void OnImGuiRenderImpl(ntt::Timestep ts) override;

        inline const cv::Mat& GetOriginalImage() const { return originalImage_; }
        inline void SetOriginalImage(const cv::Mat& image) { originalImage_ = image; }
        inline const std::vector<CoordVertex>& GetVertexes() const { return vertexes_; }
        void SetVertexes(const std::vector<CoordVertex>& vertexes);

    private:
        int minVertexes_;
        cv::Mat originalImage_;
        std::vector<std::shared_ptr<ImageProcessingStep>> steps_;
        int index_ = 0;
        std::vector<CoordVertex> vertexes_;
};
#include "ImageProcessing/PreInclude.hpp"
#include "ImageProcessing/ExtractByContour.hpp"


ExtractByContour::ExtractByContour()
    : ImageProcessingStep("Extract By Contour")
{
    useMinArea_ = 
            std::make_unique<ntt::ThreadValue<bool>>(true, storage_, "useMinArea");
    area_ = 
            std::make_unique<ntt::ThreadValue<int>>(500, 0, 1000, storage_, "area");
    minArea_ = 
            std::make_unique<ntt::ThreadValue<int>>(300, 0, 1000, storage_, "minArea"),
    maxArea_ = 
            std::make_unique<ntt::ThreadValue<int>>(600, 0, 1000, storage_, "maxArea");
}

ExtractByContour::~ExtractByContour()
{

}

cv::Mat ExtractByContour::OnProcessImpl(cv::Mat image, ImageProcessingContainer* container)
{
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::Mat originalImage = container->GetOriginalImage();

    cv::findContours(image, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    NTT_APPLICATION_DEBUG("Contour Size: {}", contours.size());

    for (size_t i = 0; i < contours.size(); i++) {
        double contourArea = cv::contourArea(contours[i]);
        if (IsValidArea(contourArea)) {
            cv::Rect boundingBox = cv::boundingRect(contours[i]);
            int centerX = boundingBox.x + boundingBox.width / 2;
            int centerY = boundingBox.y + boundingBox.height / 2;
            cv::rectangle(originalImage, boundingBox, cv::Scalar(0, 255, 0), 2);
            std::string centerText = "(" + std::to_string(centerX) + ", " + std::to_string(centerY) + ")";

            cv::putText(originalImage, centerText, cv::Point(boundingBox.x, boundingBox.y - 10),
                        cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 1);
        }
    }
    container->SetOriginalImage(originalImage);
    return image;
}

void ExtractByContour::OnImGuiRenderImpl(ntt::Timestep ts) 
{
    useMinArea_->Bind();
    area_->Bind();
    minArea_->Bind();
    maxArea_->Bind();

    ImGui::Checkbox("Use Min Area", useMinArea_->GetPointer());
    if (*(useMinArea_->GetPointer()))
    {
        ImGui::SliderInt("Area", area_->GetPointer(), area_->GetMinValue(), area_->GetMaxValue());
    }
    else
    {
        ImGui::SliderInt("Min Area", minArea_->GetPointer(), minArea_->GetMinValue(), minArea_->GetMaxValue());
        ImGui::SliderInt("Max Area", maxArea_->GetPointer(), maxArea_->GetMinValue(), maxArea_->GetMaxValue());
    }

    useMinArea_->UnBind();
    area_->UnBind();
    minArea_->UnBind();
    maxArea_->UnBind();
}

bool ExtractByContour::IsValidArea(double area)
{
    useMinArea_->Bind();
    area_->Bind();
    minArea_->Bind();
    maxArea_->Bind();
    bool result = false;
    if (*(useMinArea_->GetPointer()))
    {
        result = area > *area_->GetPointer(); 
    }
    else 
    {
        result = area < *maxArea_->GetPointer() && area > *minArea_->GetPointer();
    }
    useMinArea_->UnBind();
    area_->UnBind();
    minArea_->UnBind();
    maxArea_->UnBind();
    return result;
}
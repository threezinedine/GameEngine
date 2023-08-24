#include "ImageProcessing/PreInclude.hpp"
#include "ImageProcessing/ExtractCircularObject.hpp"


ExtractCircularObject::ExtractCircularObject()
    : ImageProcessingStep("Extract-circular-object")
{
    method_ = std::make_unique<ntt::ThreadValue<int>>(0, storage_, "method");
    dp_ = std::make_unique<ntt::ThreadValue<float>>(1, 0, 2, storage_, "dp");
    minDist_ = std::make_unique<ntt::ThreadValue<float>>(50, 10, 200, storage_, "minDistance");
    param1_ = std::make_unique<ntt::ThreadValue<float>>(200, 0, 300, storage_, "param1");
    param2_ = std::make_unique<ntt::ThreadValue<float>>(30, 0, 300, storage_, "param2");
    minRadius_ = std::make_unique<ntt::ThreadValue<int>>(10, 0, 300, storage_, "minRadius");
    maxRadius_ = std::make_unique<ntt::ThreadValue<int>>(100, 0, 300, storage_, "maxRadius");
}

ExtractCircularObject::~ExtractCircularObject()
{

}

cv::Mat ExtractCircularObject::OnProcessImpl(cv::Mat image, ImageProcessingContainer* container)
{
    cv::Mat gray, originalImage = container->GetOriginalImage();
    std::vector<cv::Vec3f> circles;
    cv::cvtColor(image, gray, cv::COLOR_RGB2GRAY);

    NTT_APPLICATION_DEBUG("Run Here");

    method_->Bind();
    NTT_APPLICATION_DEBUG("Run Here");
    dp_->Bind();
    NTT_APPLICATION_DEBUG("Run Here");
    minDist_->Bind();
    NTT_APPLICATION_DEBUG("Run Here");
    param1_->Bind();
    NTT_APPLICATION_DEBUG("Run Here");
    param2_->Bind();
    NTT_APPLICATION_DEBUG("Run Here");
    minRadius_->Bind();
    NTT_APPLICATION_DEBUG("Run Here");
    maxRadius_->Bind();
    NTT_APPLICATION_DEBUG("Run Here");

    cv::HoughCircles(
        gray,
        circles,
        // *(method_->GetPointer()),
        cv::HOUGH_GRADIENT,
        (double)dp_->GetValue(),
        (double)minDist_->GetValue(),       // Minimum distance between detected circles
        (double)param1_->GetValue(),      // Upper threshold for edge detection
        (double)param2_->GetValue(),       // Threshold for center detection
        minRadius_->GetValue(),       // Minimum radius
        maxRadius_->GetValue()       // Maximum radius
    );

    method_->UnBind();
    dp_->UnBind();
    minDist_->UnBind();
    param1_->UnBind();
    param2_->UnBind();
    minRadius_->UnBind();
    maxRadius_->UnBind();

    for (size_t i = 0; i < circles.size(); i++) {
        cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);

        cv::circle(originalImage, center, radius, cv::Scalar(0, 255, 0), 2);
        cv::circle(originalImage, center, 2, cv::Scalar(0, 0, 255), 3);
    }

    container->SetOriginalImage(originalImage);

    return image;
}

void ExtractCircularObject::OnImGuiRenderImpl(ntt::Timestep ts)
{
    method_->Bind();
    dp_->Bind();
    minDist_->Bind();
    param1_->Bind();
    param2_->Bind();
    minRadius_->Bind();
    maxRadius_->Bind();

    ImGui::SliderFloat("Dp", dp_->GetPointer(), dp_->GetMinValue(), dp_->GetMaxValue());
    ImGui::SliderFloat("Min Dist", minDist_->GetPointer(), 
                minDist_->GetMinValue(), minDist_->GetMaxValue());
    ImGui::SliderFloat("Param 1", param1_->GetPointer(), 
                param1_->GetMinValue(), param1_->GetMaxValue());
    ImGui::SliderFloat("Param 2", param2_->GetPointer(), 
                param2_->GetMinValue(), param2_->GetMaxValue());
    ImGui::SliderInt("Min Radius", minRadius_->GetPointer(), 
                minRadius_->GetMinValue(), minRadius_->GetMaxValue());
    ImGui::SliderInt("Max Radius", maxRadius_->GetPointer(), 
                maxRadius_->GetMinValue(), maxRadius_->GetMaxValue());

    method_->UnBind();
    dp_->UnBind();
    minDist_->UnBind();
    param1_->UnBind();
    param2_->UnBind();
    minRadius_->UnBind();
    maxRadius_->UnBind();
}
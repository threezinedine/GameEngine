#include "ImageProcessing/PreInclude.hpp"
#include "ImageProcessing/ExtractByColor.hpp"


static cv::Vec3b FloatPtrToVec3b(const float* colorComponents) {
    cv::Vec3b cvVec3b;
    cvVec3b[0] = static_cast<uchar>(colorComponents[0] * 255.0); // Blue
    cvVec3b[1] = static_cast<uchar>(colorComponents[1] * 255.0); // Green
    cvVec3b[2] = static_cast<uchar>(colorComponents[2] * 255.0); // Red
    return cvVec3b;
}

static cv::Scalar Vec3bToHSV(const cv::Vec3b& cvVec3b) {
    cv::Mat3b bgrColorMat(1, 1, cvVec3b);
    cv::Mat3b hsvColorMat;
    cv::cvtColor(bgrColorMat, hsvColorMat, cv::COLOR_RGB2HSV);

    cv::Scalar hsvColor = hsvColorMat.at<cv::Vec3b>(0, 0);
    return hsvColor;
}

ExtractByColor::ExtractByColor()
    : ImageProcessingStep("Extract Data By Color")
{
    lowerLimitRGB_ = 
        std::make_unique<ntt::ThreadArray<float>>(
            std::vector<float>{0.9, 0, 0}, storage_, "lowerLimit");
    upperLimitRGB_ = 
        std::make_unique<ntt::ThreadArray<float>>(
            std::vector<float>{1, 0, 0}, storage_, "upperLimit");
    area_ = std::make_unique<ntt::ThreadValue<int>>(100, 0, 1000, storage_, "area");
}

ExtractByColor::~ExtractByColor()
{

}

cv::Mat ExtractByColor::OnProcessImpl(cv::Mat image, ImageProcessingContainer* container)
{
    cv::Mat hsvImage, originalImage = container->GetOriginalImage();

    cv::cvtColor(image, hsvImage, cv::COLOR_RGB2HSV);

    lowerLimitRGB_->Bind();
    cv::Vec3b lowerLimitRGB = FloatPtrToVec3b(lowerLimitRGB_->GetPointer());
    lowerLimitRGB_->UnBind();

    upperLimitRGB_->Bind();
    cv::Vec3b upperLimitRGB = FloatPtrToVec3b(upperLimitRGB_->GetPointer());
    upperLimitRGB_->UnBind();

    cv::Scalar lowerLimitHSV = Vec3bToHSV(lowerLimitRGB);
    cv::Scalar upperLimitHSV = Vec3bToHSV(upperLimitRGB);

    cv::Mat redMask;
    cv::inRange(hsvImage, lowerLimitHSV, upperLimitHSV, redMask);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(redMask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    for (size_t i = 0; i < contours.size(); i++) {
        double contourArea = cv::contourArea(contours[i]);
        area_->Bind();
        if (contourArea > area_->GetValue()) {
            cv::Rect boundingBox = cv::boundingRect(contours[i]);
            int centerX = boundingBox.x + boundingBox.width / 2;
            int centerY = boundingBox.y + boundingBox.height / 2;
            cv::rectangle(originalImage, boundingBox, cv::Scalar(0, 255, 0), 2);
            std::string centerText = "(" + std::to_string(centerX) + ", " + std::to_string(centerY) + ")";

            cv::putText(originalImage, centerText, cv::Point(boundingBox.x, boundingBox.y - 10),
                        cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 1);
        }
        area_->UnBind();
    }
    container->SetOriginalImage(originalImage);
    return image;
}

void ExtractByColor::OnImGuiRenderImpl(ntt::Timestep ts)
{
    lowerLimitRGB_->Bind();
    ImGui::ColorPicker3("Lower Color", lowerLimitRGB_->GetPointer());
    lowerLimitRGB_->UnBind();

    upperLimitRGB_->Bind();
    ImGui::ColorPicker3("Upper Color", upperLimitRGB_->GetPointer());
    upperLimitRGB_->UnBind();

    area_->Bind();
    ImGui::SliderInt("ExtractByColor Area", area_->GetPointer(), area_->GetMinValue(), area_->GetMaxValue());
    area_->UnBind();
}
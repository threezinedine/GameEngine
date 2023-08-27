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
    hChannelRange_ =
        std::make_unique<ntt::ThreadValue<int>>(
            10, 0, 100, storage_, "hChannelRange"
        );
    sChannelLowLimitValue_ =
        std::make_unique<ntt::ThreadValue<int>>(
            100, 0, 255, storage_, "sChannelLowLimit"
        );
    vChannelLowLimtValue_ =
        std::make_unique<ntt::ThreadValue<int>>(
            100, 0, 255, storage_, "vChannelLowLimit"
        );
    sChannelUpLimitValue_ =
        std::make_unique<ntt::ThreadValue<int>>(
            200, 0, 255, storage_, "sChannelUpLimit"
        );
    vChannelUpLimtValue_ =
        std::make_unique<ntt::ThreadValue<int>>(
            200, 0, 255, storage_, "vChannelUpLimit"
        );

    detectedColor_ = 
        std::make_unique<ntt::ThreadArray<float>>(
            std::vector<float>{1, 0, 0}, storage_, "detectedColor");
    area_ = std::make_unique<ntt::ThreadValue<int>>(100, 0, 1000, storage_, "area");
}

ExtractByColor::~ExtractByColor()
{

}

cv::Mat ExtractByColor::OnProcessImpl(cv::Mat image, ImageProcessingContainer* container)
{
    PROFILE_SCOPE();

    cv::Mat hsvImage, originalImage = container->GetOriginalImage();
    std::vector<CoordVertex> vertexes;

    cv::cvtColor(image, hsvImage, cv::COLOR_RGB2HSV);

    detectedColor_->Bind();
    cv::Vec3b detectColorRGB = FloatPtrToVec3b(detectedColor_->GetPointer());
    detectedColor_->UnBind();


    hChannelRange_->Bind();
    sChannelLowLimitValue_->Bind();
    vChannelLowLimtValue_->Bind();
    sChannelUpLimitValue_->Bind();
    vChannelUpLimtValue_->Bind();

    cv::Scalar detectColorHSV = Vec3bToHSV(detectColorRGB);
    cv::Scalar lowerLimitHSV = cv::Scalar(
                                    detectColorHSV[0] - hChannelRange_->GetValue(), 
                                    sChannelLowLimitValue_->GetValue(), 
                                    vChannelLowLimtValue_->GetValue());
    cv::Scalar upperLimitHSV = cv::Scalar(
                                    detectColorHSV[0] + hChannelRange_->GetValue(), 
                                    sChannelUpLimitValue_->GetValue(), 
                                    vChannelUpLimtValue_->GetValue());

    cv::Mat redMask;
    cv::inRange(hsvImage, lowerLimitHSV, upperLimitHSV, redMask);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(redMask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    hChannelRange_->UnBind();
    sChannelLowLimitValue_->UnBind();
    vChannelLowLimtValue_->UnBind();
    sChannelUpLimitValue_->UnBind();
    vChannelUpLimtValue_->UnBind();

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

            vertexes.push_back({
                { 0, 0 }, { centerX, centerY }, false
            });
        }
        area_->UnBind();
    }

    if (vertexes.size() == 6)
    {
        std::sort(vertexes.begin(), vertexes.end(), [](CoordVertex a, CoordVertex b) -> bool
        {
            return a.imagePos.x + a.imagePos.y < b.imagePos.x + b.imagePos.y;
        });

        vertexes[0].isFixed = true;
        vertexes[0].realWorldPos = { 0.0f, 0.0f };

        vertexes[2].isFixed = true;
        vertexes[3].isFixed = true;
        if (vertexes[2].realWorldPos.x < vertexes[2].realWorldPos.y)
        {
            vertexes[2].realWorldPos = { 1.0f, 0.0f };
            vertexes[3].realWorldPos = { 0.0f, 1.0f };
        }
        else 
        {
            vertexes[2].realWorldPos = { 0.0f, 1.0f };
            vertexes[3].realWorldPos = { 1.0f, 0.0f };
        }

        vertexes[4].isFixed = true;
        vertexes[4].realWorldPos = { 1.0f, 1.0f };
    }

    container->SetVertexes(vertexes);
    container->SetOriginalImage(originalImage);
    return image;
}

void ExtractByColor::OnImGuiRenderImpl(ntt::Timestep ts)
{
    area_->Bind();
    ImGui::SliderInt("ExtractByColor Area", area_->GetPointer(), area_->GetMinValue(), area_->GetMaxValue());
    area_->UnBind();

    detectedColor_->Bind();
    ImGui::ColorPicker3("Detected Color", detectedColor_->GetPointer());
    detectedColor_->UnBind();

    hChannelRange_->Bind();
    sChannelLowLimitValue_->Bind();
    vChannelLowLimtValue_->Bind();
    sChannelUpLimitValue_->Bind();
    vChannelUpLimtValue_->Bind();

    ImGui::SliderInt("H Channel Range", hChannelRange_->GetPointer(),
                                        hChannelRange_->GetMinValue(),
                                        hChannelRange_->GetMaxValue());
    ImGui::SliderInt("S Channel Lower Limit", sChannelLowLimitValue_->GetPointer(),
                                        sChannelLowLimitValue_->GetMinValue(),
                                        sChannelLowLimitValue_->GetMaxValue());
    ImGui::SliderInt("V Channel Lower Limit", vChannelLowLimtValue_->GetPointer(),
                                        vChannelLowLimtValue_->GetMinValue(),
                                        vChannelLowLimtValue_->GetMaxValue());
    ImGui::SliderInt("S Channel Upper Limit", sChannelUpLimitValue_->GetPointer(),
                                        sChannelUpLimitValue_->GetMinValue(),
                                        sChannelUpLimitValue_->GetMaxValue());
    ImGui::SliderInt("V Channel Upper Limt", vChannelUpLimtValue_->GetPointer(),
                                        vChannelUpLimtValue_->GetMinValue(),
                                        vChannelUpLimtValue_->GetMaxValue());

    hChannelRange_->UnBind();
    sChannelLowLimitValue_->UnBind();
    vChannelLowLimtValue_->UnBind();
    sChannelUpLimitValue_->UnBind();
    vChannelUpLimtValue_->UnBind();
}
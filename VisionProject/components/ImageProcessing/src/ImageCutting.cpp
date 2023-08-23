#include "ImageProcessing/ImageProcessing.hpp"


ImageCutting::ImageCutting(int imageWidth, int imageHeight)
    : ImageProcessingStep("Image Cutting"),
        topLeftPoint_(new int[2] { 0, 0}, 0, imageWidth),
        rightButtomPoint_(new int[2] { imageWidth, imageHeight }, 0, imageWidth),
        imageWidth_(imageWidth), imageHeight_(imageHeight)
{

}

ImageCutting::~ImageCutting()
{

}

cv::Mat ImageCutting::OnProcessImpl(cv::Mat image, ImageProcessingContainer* container)
{
    topLeftPoint_.Bind();
    rightButtomPoint_.Bind();
    imageWidth_ = image.size().width;
    imageHeight_ = image.size().height;
    auto xMin = topLeftPoint_.GetPointer()[0];
    auto xMax = rightButtomPoint_.GetPointer()[0];
    auto yMin = topLeftPoint_.GetPointer()[1];
    auto yMax = rightButtomPoint_.GetPointer()[1];

    auto xRange = cv::Range(xMin, xMax);
    auto yRange = cv::Range(yMin, yMax);
    try 
    {
        image = image(yRange, xRange);
        NTT_APPLICATION_DEBUG("Image Shape: ({}, {})", image.size().width, image.size().height);
    }
    catch (std::exception& ex)
    {

    }
    topLeftPoint_.UnBind();
    rightButtomPoint_.UnBind();
    return image;
}

void ImageCutting::OnImGuiRender(ntt::Timestep ts)
{
    ImGui::Text(GetName().c_str());
    topLeftPoint_.Bind();
    ImGui::SliderInt2("Top left point", topLeftPoint_.GetPointer(), 
            topLeftPoint_.GetMinValue(), imageWidth_);
    topLeftPoint_.UnBind();

    rightButtomPoint_.Bind();
    ImGui::SliderInt2("Right Buttom point", rightButtomPoint_.GetPointer(), 
            rightButtomPoint_.GetMinValue(), imageHeight_);
    rightButtomPoint_.UnBind();
}
#include "ImageProcessing/PreInclude.hpp"
#include "ImageProcessing/ConvertImageToRGB.hpp"


ConvertImageToRGB::ConvertImageToRGB()
    : ImageProcessingStep(std::string("Convert Image To RGB"))
{

}

ConvertImageToRGB::~ConvertImageToRGB()
{

}

cv::Mat ConvertImageToRGB::OnProcessImpl(cv::Mat image, ImageProcessingContainer* container)
{
    cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
    container->SetOriginalImage(image);
    return image;
}
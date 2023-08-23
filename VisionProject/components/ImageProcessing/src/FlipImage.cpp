#include "ImageProcessing/ImageProcessing.hpp"


FlipImage::FlipImage()
    : ImageProcessingStep(std::string("Flip Image"))
{

}

FlipImage::~FlipImage()
{

}

cv::Mat FlipImage::OnProcessImpl(cv::Mat image, ImageProcessingContainer* container)
{
    cv::flip(image, image, 1);
    container->SetOriginalImage(image);
    return image;
}

void FlipImage::OnImGuiRenderImpl(ntt::Timestep ts)
{

}
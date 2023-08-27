#include "ImageProcessing/PreInclude.hpp"
#include "ImageProcessing/FlipImage.hpp"


FlipImage::FlipImage()
    : ImageProcessingStep(std::string("Flip Image"))
{

}

FlipImage::~FlipImage()
{

}

cv::Mat FlipImage::OnProcessImpl(cv::Mat image, ImageProcessingContainer* container)
{
    PROFILE_SCOPE();
    cv::flip(image, image, 1);
    container->SetOriginalImage(image);
    return image;
}

void FlipImage::OnImGuiRenderImpl(ntt::Timestep ts)
{

}
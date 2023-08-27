#include "ImageProcessing/PreInclude.hpp"
#include "ImageProcessing/ImageResize.hpp"



ImageResize::ImageResize(int width)
    : ImageProcessingStep("Image Resize"),
        width_(width), height_(-1)
{

}

ImageResize::~ImageResize()
{

}

cv::Mat ImageResize::OnProcessImpl(cv::Mat image, ImageProcessingContainer* container)
{
    PROFILE_SCOPE();

    if (height_ == -1)
    {
        int width = image.cols;
        int height = image.rows;
        double aspect_ratio = static_cast<double>(width) / height;
        height_ = static_cast<int>(width_ / aspect_ratio);
    }

    cv::resize(image, image, cv::Size(width_, height_));
    container->SetOriginalImage(image);
    return image;
}
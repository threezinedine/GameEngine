#include "ImageProcessing/ImageProcessing.hpp"


ImageProcessingContainer::ImageProcessingContainer()
    : ntt::ImGuiApplication(std::string("Image Processing Container"))
{

}

ImageProcessingContainer::~ImageProcessingContainer()
{

}

cv::Mat ImageProcessingContainer::OnProcess(cv::Mat image)
{
    for (int i=0; i<index_; i++)
    {
        try
        {
            image = steps_[i]->OnProcess(image, this);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    return image;
}

void ImageProcessingContainer::AppendStep(std::shared_ptr<ImageProcessingStep> step)
{
    steps_.insert(steps_.begin() + index_++, step);
}

void ImageProcessingContainer::PopStep(std::shared_ptr<ImageProcessingStep> step)
{
    index_--;
}

void ImageProcessingContainer::OnImGuiRenderImpl(ntt::Timestep ts)
{
    for (int i = 0; i < index_; i++)
    {
        steps_[i]->OnImGuiRender(ts);
    }
}
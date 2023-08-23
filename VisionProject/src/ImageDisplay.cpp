#include <Webcam.hpp>
#include <ImageDisplay.hpp>
#include <chrono>


ImageDisplay::ImageDisplay()
    : ntt::ImGuiApplication("Webcam"),
        imageTimePlan_(50)
{

}

ImageDisplay::~ImageDisplay()
{

}

void ImageDisplay::OnImGuiRenderImpl(ntt::Timestep ts)
{
    if (imageTimePlan_.IsTriggered())
    {
        imageData_ = WebCam::GetInstance()->GetImage();
    }

    if (!imageData_.empty())
    {
        image_.Bind();
        image_.SetImage(imageData_);
    }
}
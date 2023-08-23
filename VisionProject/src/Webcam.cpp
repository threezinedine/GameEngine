#include <thread>
#include <mutex>
#include <chrono>

#include "Webcam.hpp"


WebCam* WebCam::instance_ = nullptr;

WebCam::WebCam(int id)
    : isUseCam_(true), cap_(id), isRunning_(false), container_(nullptr)
{
    WebCam::instance_ = this;
}

WebCam::WebCam(const std::string& vidPath)
    : isUseCam_(false), cap_(vidPath), isRunning_(false), container_(nullptr)
{
    WebCam::instance_ = this;
}

WebCam::~WebCam()
{

}

void WebCam::OnUpdateImpl()
{
    std::cout << std::endl;
    if (cap_.isOpened())
    {
        {
            auto start = cv::getTickCount();
            std::lock_guard<std::mutex> lock(imageMutex_);
            cap_.read(image_);
            if (container_ != nullptr)
            {
                container_->SetOriginalImage(image_);
                image_ = container_->OnProcess(image_);
                image_ = container_->GetOriginalImage();
            }

            if (!isUseCam_)
            {
                if (image_.empty()) 
                {
                    cap_.set(cv::CAP_PROP_POS_FRAMES, 0); // Reset video position to the beginning
                }
                cv::waitKey(10);
            }
            NTT_APPLICATION_DEBUG("Processing Time: {} ms", 
                    (cv::getTickCount() - start) / cv::getTickFrequency() * 1000);
        }
    }
}

void WebCam::OnInitImpl()
{

}

const cv::Mat WebCam::GetImage()
{
    std::lock_guard<std::mutex> lock(imageMutex_);
    return image_;
}

void WebCam::OnReleaseImpl()
{
    cap_.release();
}
#pragma once
#include <string>
#include <opencv2/opencv.hpp>
#include <mutex>
#include <atomic>
#include <thread>

#include "ImageProcessing/ImageProcessing.hpp"
#include "NTTEngine/NTTEngine.hpp"


class WebCam: public ntt::NTTThread
{
    public:
        WebCam(int id);
        WebCam(const std::string& vidPath);
        virtual ~WebCam();

        void OnInitImpl() override;
        void OnUpdateImpl() override;
        void OnReleaseImpl() override;

        const cv::Mat GetImage();
        inline void SetImageProcessingContainer(std::shared_ptr<ImageProcessingContainer> container) 
        { 
            container_ = container; 
        }

        static WebCam* GetInstance() { return instance_; }
        
    private:
        static WebCam* instance_;

        bool isUseCam_;

        cv::Mat image_;
        cv::VideoCapture cap_;
        std::mutex imageMutex_;
        std::thread thread_;
        std::atomic<bool> isRunning_;
        std::shared_ptr<ImageProcessingContainer> container_;
};
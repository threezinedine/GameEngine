#include <string>
#include "ImageProcessing/PreInclude.hpp"
#include "ImageProcessing/QRDetector.hpp"


QRDetect::QRDetect()
    : ImageProcessingStep("QR Dectector")
{

}

QRDetect::~QRDetect()
{

}

cv::Mat QRDetect::OnProcessImpl(cv::Mat image, ImageProcessingContainer* container)
{
    cv::QRCodeDetector qrCodeDetector;
    cv::Mat originalImage = container->GetOriginalImage();
    cv::Point textPosition(image.cols - 200, 50);

    std::string qrCodeContent;
    std::vector<cv::String> decodedInfo;
    std::vector<cv::Point> points;

    qrCodeDetector.detectAndDecodeMulti(image, decodedInfo, points);

    for (int i=0; i<decodedInfo.size(); i++)
    {
        cv::Point qrCodeCenter(0, 0);
        for (int j = 0; j < 4; ++j) {
            cv::line(originalImage, points[i * 4 + j], points[i * 4 + (j + 1) % 4], cv::Scalar(0, 255, 0), 2);
        }
    }

    container->SetOriginalImage(originalImage);
    return image;
}

void QRDetect::OnImGuiRenderImpl(ntt::Timestep ts)
{

}
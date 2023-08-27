#include "ImageProcessing/PreInclude.hpp"
#include "ImageProcessing/PnPAlgorithm.hpp"

PnPAlgorithm::PnPAlgorithm()
    : ImageProcessingStep("Pnp Algorithm")
{

}

PnPAlgorithm::~PnPAlgorithm()
{

}

cv::Mat PnPAlgorithm::OnProcessImpl(cv::Mat image, ImageProcessingContainer* container)
{
    PROFILE_SCOPE();

    auto vertexes = container->GetVertexes();
    auto originalImage = container->GetOriginalImage();
    cv::Mat rotationMatrix;

    if (vertexes.size() == 6)
    {
        cv::Mat worldPoints(vertexes.size(), 3, CV_64F);
        cv::Mat imagePoints(vertexes.size(), 2, CV_64F);

        for (size_t i=0; i<vertexes.size(); i++) 
        {
            if (vertexes[i].isFixed)
            {
                worldPoints.at<double>(i, 0) = vertexes[i].realWorldPos.x;
                worldPoints.at<double>(i, 1) = vertexes[i].realWorldPos.y;
                worldPoints.at<double>(i, 2) = 0.0; 

                imagePoints.at<double>(i, 0) = vertexes[i].imagePos.x;
                imagePoints.at<double>(i, 1) = vertexes[i].imagePos.y;

            }
        }

        cv::Mat cameraMatrix = (cv::Mat_<float>(3, 3) << 1000, 0, 0, 0, 1000, 0, 0, 0, 1);
        cv::Mat distCoeffs = (cv::Mat_<float>(5, 1) << 0, 0, 0, 0, 0);

        cv::Mat rvec, tvec;

        cv::solvePnP(worldPoints, imagePoints, cameraMatrix, 
                        distCoeffs, rvec, tvec, cv::SOLVEPNP_ITERATIVE);

        cv::Rodrigues(rvec, rotationMatrix);

        for (size_t i=0; i<vertexes.size(); i++)
        {
            if (!vertexes[i].isFixed)
            {
                cv::Mat transformPointed = rotationMatrix * cv::Mat(
                    { vertexes[i].imagePos.x, vertexes[i].imagePos.y, 0.0f }
                ) + tvec;
                vertexes[i].realWorldPos.x = transformPointed.at<float>(0);
                vertexes[i].realWorldPos.y = transformPointed.at<float>(1);

                cv::Point textPos(vertexes[i].imagePos.x + 5, vertexes[i].imagePos.y + 5);
                std::string text = "(" + std::to_string(vertexes[i].realWorldPos.x) + ", " + 
                                    std::to_string(vertexes[i].realWorldPos.y) + ")";
                cv::putText(originalImage, text, textPos, 
                                cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
            }

        }

        container->SetOriginalImage(originalImage);
    }
    return image;
}

void PnPAlgorithm::OnImGuiRenderImpl(ntt::Timestep ts)
{

}
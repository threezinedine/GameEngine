#include "ImageProcessing/PreInclude.hpp"
#include "ImageProcessing/ImageProcessingStep.hpp"


ImageProcessingStep::ImageProcessingStep(const std::string& stepName)
    : ntt::ImGuiComponent(stepName)
{
    std::shared_ptr<ntt::IFileSystem> file 
            = std::make_shared<ntt::RealFileSystem>("./" + stepName + ".json");
    storage_ = std::make_shared<ntt::Storage>(file);

    isUsed_ = std::make_unique<ntt::ThreadValue<bool>>(true, storage_, "isUsed");
    openTree_ = std::make_unique<ntt::ThreadValue<bool>>(false, storage_, "openTree");
    displayImage_ = std::make_shared<ntt::ThreadValue<bool>>(true, storage_, "displayImage");
}


ImageProcessingStep::~ImageProcessingStep()
{
    isUsed_->Save();
    openTree_->Save();
    displayImage_->Save();
    storage_->Save();
}

cv::Mat ImageProcessingStep::OnProcess(cv::Mat mat, ImageProcessingContainer* container)
{
    PROFILE_SCOPE();

    cv::Mat result;
    isUsed_->Bind();
    bool useStep = *(isUsed_->GetPointer());
    isUsed_->UnBind();

    if (!mat.empty() && useStep)
    {
        try 
        {
            result = OnProcessImpl(mat, container);
        }
        catch (std::exception& ex)
        {
            NTT_APPLICATION_WARN("Processing Error at: {} -- Error: {}", GetName(), ex.what());
            result = mat.clone();
        }
    }
    else 
    {
        result = mat.clone();
    }

    {
        std::lock_guard<std::mutex> lock(mutex_);
        image_ = VerifyImage(result);
    }
    return result;
}

void ImageProcessingStep::OnImGuiRender(ntt::Timestep ts)
{
    // NTT_APPLICATION_DEBUG("Start ImGuiRender ({})", GetName());

    ImGui::SetNextItemOpen(openTree_->GetValue(), ImGuiCond_Once);
    if (ImGui::TreeNode(GetName().c_str()))
    {
        isUsed_->Bind();
        ImGui::Checkbox("Use?", isUsed_->GetPointer());
        isUsed_->UnBind();

        OnImGuiRenderImpl(ts);

        ImGui::Checkbox("Display Image", displayImage_->GetPointer());

        if (displayImage_->GetValue())
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (!image_.empty())
            {
                imageContext_.Bind();
                imageContext_.SetImage(image_);
            }
        }

        *(openTree_->GetPointer()) = true;
        ImGui::TreePop();
    }
    else 
    {
        *(openTree_->GetPointer()) = false;
    }
    // NTT_APPLICATION_DEBUG("End ImGuiRender ({})", GetName());
}

void ImageProcessingStep::OnImGuiRenderImpl(ntt::Timestep ts)
{

}

cv::Mat ImageProcessingStep::VerifyImage(cv::Mat image)
{
    if (image.channels() == 1)
    {
        cv::Mat rgbImage(image.rows, image.cols, CV_8UC3);

        for (int row = 0; row < image.rows; ++row) {
            for (int col = 0; col < image.cols; ++col) {
                uchar binaryValue = image.at<uchar>(row, col);
                rgbImage.at<cv::Vec3b>(row, col) = cv::Vec3b(binaryValue, binaryValue, binaryValue);
            }
        }
        return rgbImage;
    }
    else
    {
        return image.clone();
    }
}
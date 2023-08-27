#include "ImageProcessing/PreInclude.hpp"
#include "ImageProcessing/ConvertToBinary.hpp"


ConvertToBinary::ConvertToBinary()
    : ImageProcessingStep(std::string("Convert Image To Binary"))
{
    convertMethod_ = std::make_unique<ntt::ThreadValue<int>>(0, 0, 4, storage_, "convertMethod");

    threshold_ =
        std::make_unique<ntt::ThreadValue<int>>(128, 0, 256, storage_, "threshold");

    useAdaptiveThreshold_ =
        std::make_unique<ntt::ThreadValue<bool>>(true, storage_, "useAdaptiveThreshold");
    adaptiveNeighborSize_ =
        std::make_unique<ntt::ThreadValue<int>>(11, 0, 15, storage_, "adaptiveNeighborSize");
    adpativeConstantSubtracted_ =
        std::make_unique<ntt::ThreadValue<int>>(2, 0, 20, storage_, "adaptiveConstantSubtracted");
    adaptiveMethod_ =
        std::make_unique<ntt::ThreadValue<int>>(0, 0, 2, storage_, "adaptiveMethod");
}


ConvertToBinary::~ConvertToBinary()
{

}


cv::Mat ConvertToBinary::OnProcessImpl(cv::Mat image, ImageProcessingContainer* container)
{
    PROFILE_SCOPE();

    cv::Mat grayImage, binaryImage;
    cv::Mat originalImage = container->GetOriginalImage();

    cv::cvtColor(image, grayImage, cv::COLOR_RGB2GRAY);

    convertMethod_->Bind();
    useAdaptiveThreshold_->Bind();
    threshold_->Bind();
    adaptiveNeighborSize_->Bind();
    adpativeConstantSubtracted_->Bind();
    adaptiveMethod_->Bind();


    if (useAdaptiveThreshold_->GetValue())
    {
        cv::adaptiveThreshold(grayImage, binaryImage, 255, adaptiveMethod_->GetValue(), 
            convertMethod_->GetValue(), adaptiveNeighborSize_->GetValue(),
            adpativeConstantSubtracted_->GetValue());
    }
    else 
    {
        cv::threshold(grayImage, binaryImage, 
                        threshold_->GetValue(), 255, convertMethod_->GetValue());
    }

    convertMethod_->UnBind();
    useAdaptiveThreshold_->UnBind();
    threshold_->UnBind();
    adaptiveNeighborSize_->UnBind();
    adpativeConstantSubtracted_->UnBind();
    adaptiveMethod_->UnBind();

    return binaryImage;
}

void ConvertToBinary::OnImGuiRenderImpl(ntt::Timestep ts)
{
    if (ImGui::TreeNode("Convert method"))
    {
        convertMethod_->Bind();
        if (ImGui::Selectable("THRESH BINARY", *(convertMethod_->GetPointer()) == cv::THRESH_BINARY))
        {
            *(convertMethod_->GetPointer()) = cv::THRESH_BINARY;
        }
        if (ImGui::Selectable("THRESH BINARY INV", *(convertMethod_->GetPointer()) == cv::THRESH_BINARY_INV))
        {
            *(convertMethod_->GetPointer()) = cv::THRESH_BINARY_INV;
        }
        if (ImGui::Selectable("THRESH TOZERO", *(convertMethod_->GetPointer()) == cv::THRESH_TOZERO))
        {
            *(convertMethod_->GetPointer()) = cv::THRESH_TOZERO;
        }
        if (ImGui::Selectable("THRESH TOZERO INPUT", *(convertMethod_->GetPointer()) == cv::THRESH_TOZERO_INV))
        {
            *(convertMethod_->GetPointer()) = cv::THRESH_TOZERO_INV;
        }
        convertMethod_->UnBind();
        ImGui::TreePop();
    }

    useAdaptiveThreshold_->Bind();
    threshold_->Bind();
    adaptiveNeighborSize_->Bind();
    adpativeConstantSubtracted_->Bind();
    adaptiveMethod_->Bind();

    ImGui::Checkbox("Use adaptive threshold", useAdaptiveThreshold_->GetPointer());

    if (!*(useAdaptiveThreshold_->GetPointer()))
    {
        ImGui::SliderInt("Threshold", threshold_->GetPointer(), 
                            threshold_->GetMinValue(), threshold_->GetMaxValue());
    }
    else 
    {
        if (ImGui::TreeNode("Method"))
        {
            if (ImGui::Selectable("ADAPTIVE_THRESH_MEAN_C", *(adaptiveMethod_->GetPointer()) == cv::ADAPTIVE_THRESH_MEAN_C))
            {
                *(adaptiveMethod_->GetPointer()) = cv::ADAPTIVE_THRESH_MEAN_C;
            }
            if (ImGui::Selectable("ADAPTIVE_THRESH_GAUSSIAN_C", *(adaptiveMethod_->GetPointer()) == cv::ADAPTIVE_THRESH_GAUSSIAN_C))
            {
                *(adaptiveMethod_->GetPointer()) = cv::ADAPTIVE_THRESH_GAUSSIAN_C;
            }
            ImGui::TreePop();
        }

        ImGui::SliderInt("Constant Subtracted", adpativeConstantSubtracted_->GetPointer(),
                        adpativeConstantSubtracted_->GetMinValue(), 
                        adpativeConstantSubtracted_->GetMaxValue());
    }

    useAdaptiveThreshold_->UnBind();
    threshold_->UnBind();
    adaptiveNeighborSize_->UnBind();
    adpativeConstantSubtracted_->UnBind();
    adaptiveMethod_->UnBind();
}
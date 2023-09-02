#include "OveralImGuiApplication.hpp"
#include "SerialUART/SerialUART.hpp"


OveralImGuiApplication::OveralImGuiApplication()
    : ImGuiApplication("Overal Control")
{
    storage_ = std::make_shared<ntt::Storage>(
        std::make_shared<ntt::RealFileSystem>("./overal-config.json")
    );

    speedRef_M1_ = std::make_shared<ntt::ThreadValue<float>>(
        0.4f, 0, 10, storage_, "speedRef_M1" 
    );
    speedRef_M2_ = std::make_shared<ntt::ThreadValue<float>>(
        0.4f, 0, 10, storage_, "speedRef_M1" 
    );

    SerialFrameManager::Initialize(std::move(std::make_unique<UARTConnection>("COM7")));
    SerialFrameManager::StartThread();
}

OveralImGuiApplication::~OveralImGuiApplication()
{
    SerialFrameManager::StopThread();
    SerialFrameManager::Release();

    speedRef_M1_->Save();
    speedRef_M2_->Save();
    storage_->Save();
}


void OveralImGuiApplication::OnImGuiRenderImpl(ntt::Timestep ts)
{
    // UARTCom::OnImGuiRenderSta();
    SerialFrameManager::OnImGuiRender(ts);
    ImGui::Separator();

    static bool getData = false;
    ImGui::Checkbox("Get Data", &getData);

    // if (getData)
    // {
    //     if (getDataPlan_.IsTriggered())
    //     {
    //         SerialFrameManager::SubmitCommand(
    //             std::make_shared<SerialCommandGetFloat32>(0x00, currentSpeed_)
    //         );
    //     }

    //     // isOn_.Bind();
    //     // ImGui::Checkbox("Is On", isOn_.GetPointer());
    //     // isOn_.UnBind();

    //     currentSpeed_.Bind();
    //     std::string speedRefStr = std::string("Speed Ref: ") + std::to_string(currentSpeed_.GetValue());
    //     ImGui::Text(speedRefStr.c_str());
    //     currentSpeed_.UnBind();
    //     ImGui::Separator();
    // }

    ImGui::Separator();
    if(ImGui::Button("Start"))
    {
        SerialFrameManager::SubmitCommand(
            std::make_shared<SerialCommandChangeBool>(0x00, true)
        );
    }
    ImGui::SameLine();
    if(ImGui::Button("Stop"))
    {
        SerialFrameManager::SubmitCommand(
            std::make_shared<SerialCommandChangeBool>(0x00, false)
        );
    }

    ImGui::Separator();
    // ImGui::Checkbox("Forward M1", forward_M1_->GetPointer());
    ImGui::SliderFloat("Speed Ref M1", speedRef_M1_->GetPointer(), 
                        speedRef_M1_->GetMinValue(), speedRef_M1_->GetMaxValue());
    // if (ImGui::Button("Send Direction M1"))
    // {
    //     SerialFrameManager::SubmitCommand(
    //         std::make_shared<UARTChangeCoilCommand>(0x01, forward_M1_->GetValue())
    //     );
    // }

    ImGui::SameLine();
    if (ImGui::Button("Send Ref M1"))
    {
        SerialFrameManager::SubmitCommand(
            std::make_shared<SerialCommandChangeFloat32>(0x00, speedRef_M1_->GetValue())
        );
    }
    ImGui::Separator();

    // ImGui::Checkbox("Forward M2", forward_M2_->GetPointer());
    ImGui::SliderFloat("Speed Ref M2", speedRef_M2_->GetPointer(), 
                        speedRef_M2_->GetMinValue(), speedRef_M2_->GetMaxValue());

    // if (ImGui::Button("Send Direction M2"))
    // {
    //     SerialFrameManager::SubmitCommand(
    //         std::make_shared<UARTChangeCoilCommand>(0x02, forward_M2_->GetValue())
    //     );
    // }
    ImGui::SameLine();
    if (ImGui::Button("Send Ref M2"))
    {
        SerialFrameManager::SubmitCommand(
            std::make_shared<SerialCommandChangeFloat32>(0x02, speedRef_M2_->GetValue())
        );
    }

    ImGui::Separator();
    // ImGui::InputFloat("Kp", kp_->GetPointer(), 
    //                     kp_->GetMinValue(), kp_->GetMaxValue());
    // ImGui::SameLine();
    // if (ImGui::Button("Change Kp"))
    // {
    //     SerialFrameManager::SubmitCommand(
    //         std::make_shared<SerialCommandChangeFloat32>(0x08, kp_->GetValue())
    //     );
    // }
    // ImGui::InputFloat("Ki", ki_->GetPointer(), 
    //                     ki_->GetMinValue(), ki_->GetMaxValue());
    // ImGui::SameLine();
    // if (ImGui::Button("Change Ki"))
    // {
    //     SerialFrameManager::SubmitCommand(
    //         std::make_shared<SerialCommandChangeFloat32>(0x0a, ki_->GetValue())
    //     );
    // }
    // ImGui::InputFloat("Kd", kd_->GetPointer(), 
    //                     kd_->GetMinValue(), kd_->GetMaxValue());
    // ImGui::SameLine();
    // if (ImGui::Button("Change Kd"))
    // {
    //     SerialFrameManager::SubmitCommand(
    //         std::make_shared<SerialCommandChangeFloat32>(0x0c, kd_->GetValue())
    //     );
    // }
}
#include "UartImGuiApplication.hpp"
#include "UART/UART.hpp"


UartImGuiApplication::UartImGuiApplication()
    : ntt::ImGuiApplication("Uart window"),
        status_(UART_NONE),
        getDataPlan_(500), currentSpeed_(0.0f, 0, 10),
        isOn_(false, false, false)
{
    std::shared_ptr<ntt::IFileSystem> file = std::make_shared<ntt::RealFileSystem>("./uart-config.json");
    storage_ = std::make_shared<ntt::Storage>(file);

    speedRef_M1_ = std::make_shared<ntt::ThreadValue<float>>(storage_->GetValue<float>("speedRef_M1", 0.4f), 0, 10);
    speedRef_M2_ = std::make_shared<ntt::ThreadValue<float>>(storage_->GetValue<float>("speedRef_M2", 0.4f), 0, 10);
    forward_M1_ = std::make_shared<ntt::ThreadValue<bool>>(storage_->GetValue<bool>("forward_M1", false), false, false);
    forward_M2_ = std::make_shared<ntt::ThreadValue<bool>>(storage_->GetValue<bool>("forward_M2", false), false, false);

    kp_ = std::make_shared<ntt::ThreadValue<float>>(storage_->GetValue<float>("kp", 1.0f), 0, 5);
    ki_ = std::make_shared<ntt::ThreadValue<float>>(storage_->GetValue<float>("ki", 1.0f), 0, 5);
    kd_ = std::make_shared<ntt::ThreadValue<float>>(storage_->GetValue<float>("kd", 1.0f), 0, 5);

}

UartImGuiApplication::~UartImGuiApplication()
{
    storage_->SetValue<float>("speedRef_M1", speedRef_M1_->GetValue());
    storage_->SetValue<float>("speedRef_M2", speedRef_M2_->GetValue());
    storage_->SetValue<bool>("forward_M1", forward_M1_->GetValue());
    storage_->SetValue<bool>("forward_M2", forward_M2_->GetValue());
    storage_->SetValue<float>("kp", kp_->GetValue());
    storage_->SetValue<float>("ki", ki_->GetValue());
    storage_->SetValue<float>("kd", kd_->GetValue());

    storage_->Save();
}

void UartImGuiApplication::OnImGuiRenderImpl(ntt::Timestep ts)
{
    UARTCom::OnImGuiRenderSta();
    ImGui::Separator();

    static bool getData = false;
    ImGui::Checkbox("Get Data", &getData);

    if (getData)
    {
        if (getDataPlan_.IsTriggered())
        {
            UARTCom::SubmitCommand(
                std::make_shared<UARTGetFloatCommand>(0x00, currentSpeed_)
            );
        }

        isOn_.Bind();
        ImGui::Checkbox("Is On", isOn_.GetPointer());
        isOn_.UnBind();

        currentSpeed_.Bind();
        std::string speedRefStr = std::string("Speed Ref: ") + std::to_string(currentSpeed_.GetValue());
        ImGui::Text(speedRefStr.c_str());
        currentSpeed_.UnBind();
        ImGui::Separator();
    }

    if (ImGui::Button("Connect"))
    {
        UARTCom::StartConnectionSta();
    }
    ImGui::SameLine();
    if (ImGui::Button("Disconnect"))
    {
        UARTCom::FinishConnectionSta();
    }

    ImGui::Separator();
    if(ImGui::Button("Start"))
    {
        UARTCom::SubmitCommand(std::make_shared<UARTChangeCoilCommand>(0x00, true));
    }

    if(ImGui::Button("Stop"))
    {
        UARTCom::SubmitCommand(std::make_shared<UARTChangeCoilCommand>(0x00, false));
    }

    ImGui::Separator();
    ImGui::Checkbox("Forward M1", forward_M1_->GetPointer());
    ImGui::SliderFloat("Speed Ref M1", speedRef_M1_->GetPointer(), 
                        speedRef_M1_->GetMinValue(), speedRef_M1_->GetMaxValue());
    if (ImGui::Button("Send Direction M1"))
    {
        UARTCom::SubmitCommand(
            std::make_shared<UARTChangeCoilCommand>(0x01, forward_M1_->GetValue())
        );
    }

    if (ImGui::Button("Send Ref M1"))
    {
        UARTCom::SubmitCommand(
            std::make_shared<UARTChangeFloatCommand>(0x02, speedRef_M1_->GetValue())
        );
    }
    ImGui::Separator();

    ImGui::Checkbox("Forward M2", forward_M2_->GetPointer());
    ImGui::SliderFloat("Speed Ref M2", speedRef_M2_->GetPointer(), 
                        speedRef_M2_->GetMinValue(), speedRef_M2_->GetMaxValue());

    if (ImGui::Button("Send Direction M2"))
    {
        UARTCom::SubmitCommand(
            std::make_shared<UARTChangeCoilCommand>(0x02, forward_M2_->GetValue())
        );
    }

    if (ImGui::Button("Send Ref M2"))
    {
        UARTCom::SubmitCommand(
            std::make_shared<UARTChangeFloatCommand>(0x06, speedRef_M2_->GetValue())
        );
    }

    ImGui::InputFloat("Kp", kp_->GetPointer(), 
                        kp_->GetMinValue(), kp_->GetMaxValue());
    ImGui::SameLine();
    if (ImGui::Button("Change Kp"))
    {
        UARTCom::SubmitCommand(
            std::make_shared<UARTChangeFloatCommand>(0x08, kp_->GetValue())
        );
    }
    ImGui::InputFloat("Ki", ki_->GetPointer(), 
                        ki_->GetMinValue(), ki_->GetMaxValue());
    ImGui::SameLine();
    if (ImGui::Button("Change Ki"))
    {
        UARTCom::SubmitCommand(
            std::make_shared<UARTChangeFloatCommand>(0x0a, ki_->GetValue())
        );
    }
    ImGui::InputFloat("Kd", kd_->GetPointer(), 
                        kd_->GetMinValue(), kd_->GetMaxValue());
    ImGui::SameLine();
    if (ImGui::Button("Change Kd"))
    {
        UARTCom::SubmitCommand(
            std::make_shared<UARTChangeFloatCommand>(0x0c, kd_->GetValue())
        );
    }
}
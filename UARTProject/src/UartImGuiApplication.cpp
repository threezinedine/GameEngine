#include "UartImGuiApplication.hpp"
#include "UART/UART.hpp"


UartImGuiApplication::UartImGuiApplication(UARTCom& com)
    : ntt::ImGuiApplication("Uart window"),
        com_(com), status_(UART_NONE),
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

    selectableVector_ = std::make_shared<ntt::ImGuiSelectableVector<std::string>>(
        std::vector<std::pair<std::string, std::string>>
        {
            { std::string("COM7"), std::string("COM7") },
            { std::string("COM6"), std::string("COM6") },
            { std::string("COM5"), std::string("COM5") },
        },
        [&com]() -> std::string 
        {
            return com.GetCom();
        },
        [&com](std::string value)
        {
            com.SetCom(value);
        }
    );
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
    selectableVector_->OnImGuiRender();
    ImGui::Separator();

    static bool getData = false;
    ImGui::Checkbox("Get Data", &getData);

    if (getData)
    {
        if (getDataPlan_.IsTriggered())
        {
            std::shared_ptr<UARTCommand> command = std::make_shared<UARTGetCoilCommand>(com_, 0x00, isOn_);
            std::shared_ptr<UARTCommand> command1 
                = std::make_shared<UARTGetFloatCommand>(com_, 0x00, 0x01, currentSpeed_);

            com_.RunCommand(command);
            com_.RunCommand(command1);
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
        com_.StartConnection();
    }
    ImGui::SameLine();
    if (ImGui::Button("Disconnect"))
    {
        com_.StopConnection();
    }

    ImGui::Separator();
    if(ImGui::Button("Start"))
    {
        std::shared_ptr<UARTCommand> command 
            = std::make_shared<UARTChangeCoilCommand>(com_, 0x00, true);
        com_.RunCommand(command);
    }

    if(ImGui::Button("Stop"))
    {
        std::shared_ptr<UARTCommand> command 
            = std::make_shared<UARTChangeCoilCommand>(com_, 0x00, false);
        com_.RunCommand(command);
    }

    ImGui::Separator();
    ImGui::Checkbox("Forward M1", forward_M1_->GetPointer());
    ImGui::SliderFloat("Speed Ref M1", speedRef_M1_->GetPointer(), 
                        speedRef_M1_->GetMinValue(), speedRef_M1_->GetMaxValue());
    if (ImGui::Button("Send Ref M1"))
    {
        std::shared_ptr<UARTCommand> command 
            = std::make_shared<UARTChangeFloatCommand>(com_, 0x02, 0x03, speedRef_M1_->GetValue());
        std::shared_ptr<UARTCommand> command2
            = std::make_shared<UARTChangeCoilCommand>(com_, 0x01, speedRef_M1_->GetValue());
        com_.RunCommand(command);
        com_.RunCommand(command2);
    }
    ImGui::Separator();

    ImGui::Checkbox("Forward M2", forward_M2_->GetPointer());
    ImGui::SliderFloat("Speed Ref M2", speedRef_M2_->GetPointer(), 
                        speedRef_M2_->GetMinValue(), speedRef_M2_->GetMaxValue());
    if (ImGui::Button("Send Ref M2"))
    {
        std::shared_ptr<UARTCommand> command 
            = std::make_shared<UARTChangeFloatCommand>(com_, 0x06, 0x07, speedRef_M2_->GetValue());
        std::shared_ptr<UARTCommand> command2
            = std::make_shared<UARTChangeCoilCommand>(com_, 0x02, speedRef_M2_->GetValue());
        com_.RunCommand(command);
        com_.RunCommand(command2);
    }

    ImGui::InputFloat("Kp", kp_->GetPointer(), 
                        kp_->GetMinValue(), kp_->GetMaxValue());
    ImGui::SameLine();
    if (ImGui::Button("Change Kp"))
    {
        std::shared_ptr<UARTCommand> commandKp 
            = std::make_shared<UARTChangeFloatCommand>(com_, 0x08, 0x09, kp_->GetValue());
        com_.RunCommand(commandKp);
    }
    ImGui::InputFloat("Ki", ki_->GetPointer(), 
                        ki_->GetMinValue(), ki_->GetMaxValue());
    ImGui::SameLine();
    if (ImGui::Button("Change Ki"))
    {
        std::shared_ptr<UARTCommand> commandKi 
            = std::make_shared<UARTChangeFloatCommand>(com_, 0x0a, 0x0b, ki_->GetValue());
        com_.RunCommand(commandKi);
    }
    ImGui::InputFloat("Kd", kd_->GetPointer(), 
                        kd_->GetMinValue(), kd_->GetMaxValue());
    ImGui::SameLine();
    if (ImGui::Button("Change Kd"))
    {
        std::shared_ptr<UARTCommand> commandKd 
            = std::make_shared<UARTChangeFloatCommand>(com_, 0x0c, 0x0d, kd_->GetValue());
        com_.RunCommand(commandKd);
    }
}
#pragma once

#include <memory>
#include "UART/UART.hpp"
#include "NTTEngine/NTTEngine.hpp"
#include "Storage.hpp"


class UartImGuiApplication: public ntt::ImGuiApplication
{
    public:
        UartImGuiApplication(UARTCom& com);
        ~UartImGuiApplication();

        void OnImGuiRenderImpl(ntt::Timestep ts) override;

    private:
        std::shared_ptr<ntt::Storage> storage_;

        std::shared_ptr<ntt::ThreadValue<float>> speedRef_M1_;
        std::shared_ptr<ntt::ThreadValue<float>> speedRef_M2_;

        std::shared_ptr<ntt::ThreadValue<bool>> forward_M1_;
        std::shared_ptr<ntt::ThreadValue<bool>> forward_M2_;

        std::shared_ptr<ntt::ThreadValue<float>> kp_;
        std::shared_ptr<ntt::ThreadValue<float>> ki_;
        std::shared_ptr<ntt::ThreadValue<float>> kd_;
        ntt::ThreadValue<float> currentSpeed_;
        ntt::ThreadValue<bool> isOn_;

        UARTCom& com_;
        ConnectionStatus status_;
        ntt::TimePlan getDataPlan_;

        std::shared_ptr<ntt::ImGuiSelectableVector<std::string>> selectableVector_;
};
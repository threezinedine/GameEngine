#pragma once
#include <memory>
#include "NTTEngine/NTTEngine.hpp"
#include "Storage.hpp"


class OveralImGuiApplication: public ntt::ImGuiApplication
{
    public:
        OveralImGuiApplication();
        ~OveralImGuiApplication();

        void OnImGuiRenderImpl(ntt::Timestep ts) override;

    private:
        std::shared_ptr<ntt::Storage> storage_;

        std::shared_ptr<ntt::ThreadValue<float>> speedRef_M1_;
        std::shared_ptr<ntt::ThreadValue<float>> speedRef_M2_;

        // std::shared_ptr<ntt::ThreadValue<float>> kp_;
        // std::shared_ptr<ntt::ThreadValue<float>> ki_;
        // std::shared_ptr<ntt::ThreadValue<float>> kd_;
        // ntt::ThreadValue<float> currentSpeed_;
        // ntt::ThreadValue<bool> isOn_;

        ntt::TimePlan getDataPlan_;

};
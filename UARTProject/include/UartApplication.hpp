#pragma once

#include "UART/UART.hpp"
#include "NTTEngine/NTTEngine.hpp"


class UartApplication: public ntt::Application 
{
    public:
        UartApplication();
        ~UartApplication();

        void OnSetupImpl() override;
        void OnUpdateImpl(ntt::Timestep ts) override;

        void OnWindowCloseImpl(ntt::WindowCloseEvent& event) override;

    private:
};
#pragma once
#include "UartCommand.hpp"

class UARTGetFloatCommand: public UARTCommand
{
    public:
        UARTGetFloatCommand(unsigned char firstAddr, ntt::ThreadValue<float>& value);
        ~UARTGetFloatCommand();

    protected:
        void OnRunImpl();

    private:
        unsigned char firstAddr_;
        ntt::ThreadValue<float>& value_;
};

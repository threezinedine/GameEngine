#pragma once
#include "UartCommand.hpp"


class UARTChangeFloatCommand: public UARTCommand
{
    public:
        UARTChangeFloatCommand(unsigned char firstAddr, float value);
        ~UARTChangeFloatCommand();

    protected:
        void OnRunImpl();

    private:
        unsigned char firstAddr_;
        float value_;
};
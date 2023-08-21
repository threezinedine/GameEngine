#pragma once
#include "UartCommand.hpp"


class UARTChangeFloatCommand: public UARTCommand
{
    public:
        UARTChangeFloatCommand(UARTCom& com, unsigned char highAdd, unsigned char lowAdd, float value);
        ~UARTChangeFloatCommand();

    protected:
        void OnRunImpl(UARTCom& com);

    private:
        unsigned char highAdd_;
        unsigned char lowAdd_;
        float value_;
};
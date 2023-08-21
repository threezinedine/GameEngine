#pragma once
#include "UartCommand.hpp"

class UARTGetFloatCommand: public UARTCommand
{
    public:
        UARTGetFloatCommand(UARTCom& com, unsigned char highAdd,
                                unsigned char lowAdd, ntt::ThreadValue<float>& value);
        ~UARTGetFloatCommand();

    protected:
        void OnRunImpl(UARTCom& com);

    private:
        unsigned char highAdd_;
        unsigned char lowAdd_;
        ntt::ThreadValue<float>& value_;
};

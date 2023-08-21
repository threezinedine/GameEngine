#pragma once
#include "UartCommand.hpp"

class UARTGetFloatCommand: public UARTCommand
{
    public:
        UARTGetFloatCommand(unsigned char highAdd,
                                unsigned char lowAdd, ntt::ThreadValue<float>& value);
        ~UARTGetFloatCommand();

    protected:
        void OnRunImpl();

    private:
        unsigned char highAdd_;
        unsigned char lowAdd_;
        ntt::ThreadValue<float>& value_;
};

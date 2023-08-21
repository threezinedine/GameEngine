#pragma once
#include "UartCommand.hpp"

class UARTGetCoilCommand: public UARTCommand
{
    public:
        UARTGetCoilCommand(unsigned char coilAddress, ntt::ThreadValue<bool>& activeVar);
        ~UARTGetCoilCommand();

    protected:
        void OnRunImpl();

    private:
        unsigned char coilAddress_;
        ntt::ThreadValue<bool>& active_;
};

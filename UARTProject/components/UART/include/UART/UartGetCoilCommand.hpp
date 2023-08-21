#pragma once
#include "UartCommand.hpp"

class UARTGetCoilCommand: public UARTCommand
{
    public:
        UARTGetCoilCommand(UARTCom& com, unsigned char coilAddress, ntt::ThreadValue<bool>& activeVar);
        ~UARTGetCoilCommand();

    protected:
        void OnRunImpl(UARTCom& com);

    private:
        unsigned char coilAddress_;
        ntt::ThreadValue<bool>& active_;
};

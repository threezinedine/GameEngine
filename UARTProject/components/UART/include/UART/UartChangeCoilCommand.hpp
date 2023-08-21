#pragma once
#include "UartCommand.hpp"


class UARTChangeCoilCommand: public UARTCommand
{
    public:
        UARTChangeCoilCommand(UARTCom& com, unsigned char coilAddress, bool active);
        ~UARTChangeCoilCommand();

    protected:
        void OnRunImpl(UARTCom& com);

    private:
        unsigned char coilAddress_;
        bool active_;
};
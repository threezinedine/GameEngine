#pragma once
#include "UartCommand.hpp"


class UARTChangeCoilCommand: public UARTCommand
{
    public:
        UARTChangeCoilCommand(unsigned char coilAddress, bool active);
        ~UARTChangeCoilCommand();

    protected:
        void OnRunImpl();

    private:
        unsigned char coilAddress_;
        bool active_;
};
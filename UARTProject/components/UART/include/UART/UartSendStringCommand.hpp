#pragma once
#include <string>
#include "UartCommand.hpp"


class UARTSendStringCommand: public UARTCommand
{
    public:
        UARTSendStringCommand(unsigned char function, const std::string& data);
        ~UARTSendStringCommand();

    protected:
        void OnRunImpl();

    private:
        unsigned char function_;
        std::string data_;        
};

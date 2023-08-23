#include "UART/UART.hpp"


UARTSendStringCommand::UARTSendStringCommand(unsigned char function, const std::string& data)
    : function_(function), data_(data)
{

}

UARTSendStringCommand::~UARTSendStringCommand()
{

}

void UARTSendStringCommand::OnRunImpl()
{
    std::vector<unsigned char> sendData;
    sendData.push_back(function_);

    for (int i=0; i<data_.length(); i++)
    {
        sendData.push_back(data_[i]);
    }

    UARTCom::GetInstance()->SendData(sendData);
}
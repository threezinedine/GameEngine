#include "UART/UART.hpp"


UARTChangeFloatCommand::UARTChangeFloatCommand(unsigned char firstAddr, float value)
    : firstAddr_(firstAddr), value_(value)
{

}


UARTChangeFloatCommand::~UARTChangeFloatCommand()
{

}

void UARTChangeFloatCommand::OnRunImpl()
{
    UARTCom::GetInstance()->ChangeFloat(firstAddr_, value_);
}
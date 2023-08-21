#include "UART/UART.hpp"


UARTChangeFloatCommand::UARTChangeFloatCommand(unsigned char highAdd, 
            unsigned char lowAdd, float value)
    : highAdd_(highAdd), lowAdd_(lowAdd), value_(value)
{

}


UARTChangeFloatCommand::~UARTChangeFloatCommand()
{

}

void UARTChangeFloatCommand::OnRunImpl()
{
    UARTCom::GetInstance()->ChangeFloat(highAdd_, lowAdd_, value_);
}
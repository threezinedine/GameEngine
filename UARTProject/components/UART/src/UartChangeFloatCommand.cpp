#include "UART/UART.hpp"


UARTChangeFloatCommand::UARTChangeFloatCommand(UARTCom& com, unsigned char highAdd, 
            unsigned char lowAdd, float value)
    : UARTCommand(com), highAdd_(highAdd), lowAdd_(lowAdd), value_(value)
{

}


UARTChangeFloatCommand::~UARTChangeFloatCommand()
{

}

void UARTChangeFloatCommand::OnRunImpl(UARTCom& com)
{
    com.ChangeFloat(highAdd_, lowAdd_, value_);
}
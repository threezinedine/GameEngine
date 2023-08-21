#include "UART/UART.hpp"


UARTGetFloatCommand::UARTGetFloatCommand(UARTCom& com, unsigned char highAdd,
                                unsigned char lowAdd, ntt::ThreadValue<float>& value)
    : UARTCommand(com), highAdd_(highAdd), lowAdd_(lowAdd), value_(value)
{

}

UARTGetFloatCommand::~UARTGetFloatCommand()
{

}

void UARTGetFloatCommand::OnRunImpl(UARTCom& com)
{
    value_.Bind();
    com.GetFloat(highAdd_, lowAdd_, value_.GetPointer());
    value_.UnBind();
}
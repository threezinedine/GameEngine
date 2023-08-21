#include "UART/UART.hpp"


UARTGetFloatCommand::UARTGetFloatCommand(unsigned char highAdd,
                                unsigned char lowAdd, ntt::ThreadValue<float>& value)
    : highAdd_(highAdd), lowAdd_(lowAdd), value_(value)
{

}

UARTGetFloatCommand::~UARTGetFloatCommand()
{

}

void UARTGetFloatCommand::OnRunImpl()
{
    value_.Bind();
    UARTCom::GetInstance()->GetFloat(highAdd_, lowAdd_, value_.GetPointer());
    value_.UnBind();
}
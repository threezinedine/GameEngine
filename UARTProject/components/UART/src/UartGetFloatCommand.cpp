#include "UART/UART.hpp"


UARTGetFloatCommand::UARTGetFloatCommand(unsigned char firstAddr, ntt::ThreadValue<float>& value)
    : firstAddr_(firstAddr), value_(value)
{

}

UARTGetFloatCommand::~UARTGetFloatCommand()
{

}

void UARTGetFloatCommand::OnRunImpl()
{
    value_.Bind();
    UARTCom::GetInstance()->GetFloat(firstAddr_, value_.GetPointer());
    value_.UnBind();
}
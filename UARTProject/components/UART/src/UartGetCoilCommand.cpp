#include "UART/UART.hpp"


UARTGetCoilCommand::UARTGetCoilCommand(UARTCom& com, unsigned char coilAddress, 
        ntt::ThreadValue<bool>& activeVar)
    : UARTCommand(com), coilAddress_(coilAddress), active_(activeVar)
{

}

UARTGetCoilCommand::~UARTGetCoilCommand()
{

}

void UARTGetCoilCommand::OnRunImpl(UARTCom& com)
{
    active_.Bind();
    com.GetCoil(coilAddress_, active_.GetPointer());
    active_.UnBind();
}
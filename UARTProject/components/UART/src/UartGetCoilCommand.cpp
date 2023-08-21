#include "UART/UART.hpp"


UARTGetCoilCommand::UARTGetCoilCommand(unsigned char coilAddress, 
        ntt::ThreadValue<bool>& activeVar)
    : coilAddress_(coilAddress), active_(activeVar)
{

}

UARTGetCoilCommand::~UARTGetCoilCommand()
{

}

void UARTGetCoilCommand::OnRunImpl()
{
    active_.Bind();
    UARTCom::GetInstance()->GetCoil(coilAddress_, active_.GetPointer());
    active_.UnBind();
}
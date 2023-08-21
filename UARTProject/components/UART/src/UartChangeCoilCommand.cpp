#include "UART/UARTCom.hpp"
#include "UART/UartChangeCoilCommand.hpp"


UARTChangeCoilCommand::UARTChangeCoilCommand(unsigned char coilAddress, bool active)
    : coilAddress_(coilAddress), active_(active)
{

}

UARTChangeCoilCommand::~UARTChangeCoilCommand()
{

}

void UARTChangeCoilCommand::OnRunImpl()
{
    UARTCom::GetInstance()->ChangeCoil(coilAddress_, active_);
}
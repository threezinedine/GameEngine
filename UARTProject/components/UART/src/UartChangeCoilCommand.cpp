#include "UART/UARTCom.hpp"
#include "UART/UartChangeCoilCommand.hpp"


UARTChangeCoilCommand::UARTChangeCoilCommand(UARTCom& com, unsigned char coilAddress, bool active)
    : UARTCommand(com), coilAddress_(coilAddress), active_(active)
{

}

UARTChangeCoilCommand::~UARTChangeCoilCommand()
{

}

void UARTChangeCoilCommand::OnRunImpl(UARTCom& com)
{
    com.ChangeCoil(coilAddress_, active_);
}
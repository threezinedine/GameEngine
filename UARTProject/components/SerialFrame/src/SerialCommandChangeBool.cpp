#include "SerialFrame/PreInclude.hpp"
#include "SerialFrame/SerialCommandChangeBool.hpp"
#include "SerialFrame/SerialFrameManager.hpp"


SerialCommandChangeBool::SerialCommandChangeBool(uint8_t addr, bool active)
    : addr_(addr), active_(active)
{

}

SerialFrameResult SerialCommandChangeBool::OnRun(SerialFrameManager* manager)
{
    std::vector<uint8_t> response;
    std::vector<uint8_t> sendData = {
        0x01, addr_, static_cast<uint8_t>(active_ ? 0x01 : 0x00),
    };

    return manager->SendData(sendData, response);
}
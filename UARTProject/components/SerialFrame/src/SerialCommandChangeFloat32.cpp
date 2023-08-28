#include "SerialFrame/PreInclude.hpp"
#include "SerialFrame/SerialCommandChangeFloat32.hpp"


SerialCommandChangeFloat32::SerialCommandChangeFloat32(uint8_t firstAddr, float value)
    : firstAddr_(firstAddr), value_(value)
{

}

SerialFrameResult SerialCommandChangeFloat32::OnRun(SerialFrameManager* manager)
{
    std::vector<uint8_t> response;
    Float32 floatValue;
    floatValue.value = value_;

    uint8_t finalAddr = firstAddr_ + 0x01;

    return manager->SendData({
        0x04, firstAddr_, finalAddr, 
        floatValue.buffer[0].buffer[0], floatValue.buffer[0].buffer[1],
        floatValue.buffer[1].buffer[0], floatValue.buffer[1].buffer[1],
    }, response);
}
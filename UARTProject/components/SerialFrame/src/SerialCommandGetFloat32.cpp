#include "SerialFrame/PreInclude.hpp"
#include "SerialFrame/SerialCommandGetFloat32.hpp"


SerialCommandGetFloat32::SerialCommandGetFloat32(uint8_t firstAddr, ntt::ThreadValue<float>& value)
    : firstAddr_(firstAddr), value_(value)
{

}

SerialFrameResult SerialCommandGetFloat32::OnRun(SerialFrameManager* manager)
{
    Float32 floatValue;
    floatValue.value = 0;
    std::vector<uint8_t> response;

    uint8_t finalAddr = firstAddr_ + 0x01;

    auto result = manager->SendData({
        0x08, firstAddr_, finalAddr, 
    }, response);

    floatValue.buffer[0].buffer[0] = response[7]; 
    floatValue.buffer[0].buffer[1] = response[8];
    floatValue.buffer[1].buffer[0] = response[9]; 
    floatValue.buffer[1].buffer[1] = response[10];

    value_.Bind();
    *(value_.GetPointer()) = floatValue.value;
    value_.UnBind();

    return result;
}
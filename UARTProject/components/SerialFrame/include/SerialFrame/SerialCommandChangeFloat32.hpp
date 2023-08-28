#pragma once
#include <cstdint>
#include "ISerialCommand.hpp"
#include "SerialFrameResultStatus.hpp"


class SerialCommandChangeFloat32: public ISerialCommand
{
    public:
        SerialCommandChangeFloat32(uint8_t firstAddr, float value);

        SerialFrameResult OnRun(SerialFrameManager* manager) override;

    private:
        uint8_t firstAddr_;
        float value_;
};
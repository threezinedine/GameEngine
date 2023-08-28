#pragma once
#include <cstdint>
#include "ISerialCommand.hpp"
#include "SerialFrameResultStatus.hpp"
#include "NTTEngineThreadSystem/ThreadValue.hpp"


class SerialCommandGetFloat32: public ISerialCommand
{
    public:
        SerialCommandGetFloat32(uint8_t firstAddr, ntt::ThreadValue<float>& value);

        SerialFrameResult OnRun(SerialFrameManager* manager) override;

    private:
        uint8_t firstAddr_;
        ntt::ThreadValue<float>& value_;
};
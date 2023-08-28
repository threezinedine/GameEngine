#pragma once
#include <vector>
#include <cstdint>
#include "SerialFrameResultStatus.hpp"
#include "NTTEngineImGuiLayerSystem/NTTEngineImGuiLayerSystem.hpp"


class IConnection: public ntt::IImGuiRenderer
{
    public:
        virtual ~IConnection() = default;

        virtual bool IsConnected() = 0;
        virtual SerialFrameResult Connect() = 0;
        virtual void Disconnect() = 0;

        virtual std::vector<uint8_t> SendRequets(std::vector<uint8_t> request, bool needRes = false) = 0;
};
#pragma once
#include <memory>
#include <Windows.h>
#include "SerialFrame/SerialFrame.hpp"
#include "Storage.hpp"
#include "NTTEngineImGuiTools/NTTEngineImGuiTools.hpp"
#include "NTTEngineThreadSystem/NTTEngineThreadSystem.hpp"


class UARTConnection: public IConnection
{
    public:
        UARTConnection(const std::string& name, const char* comPort = "COM7", int baudrate = 115200);
        virtual ~UARTConnection();

        virtual bool IsConnected() override;
        virtual SerialFrameResult Connect() override;
        virtual void Disconnect() override;

        virtual std::vector<uint8_t> SendRequets(std::vector<uint8_t> request, bool needRes = false) override;

        virtual void OnImGuiRender(ntt::Timestep ts) override;
        virtual const std::string& GetName() const { return name_; }

    private:
        std::string name_;
        std::string comPort_;
        HANDLE hCom_;
        DCB serialParam_ = { 0 };
        COMMTIMEOUTS timeOut_ = { 0 };
        DWORD bytesRead;
        unsigned char buffer_[100];

        std::shared_ptr<ntt::Storage> storage_; 
        std::shared_ptr<ntt::ThreadValue<int>> baudrate_;
        std::shared_ptr<ntt::ImGuiSelectableVector<std::string>> selectableVectorCom_;
        std::shared_ptr<ntt::ImGuiSelectableVector<int>> selectableVectorBaudrate_;

        ntt::ThreadValue<bool> isConnected_;
};
#pragma once
#include <memory>
#include <string>
#include <vector>
#include <queue>
#include <functional>
#include "Windows.h"
#include "UART/UARTCom.hpp"
#include "NTTEngineThreadSystem/NTTEngineThreadSystem.hpp"
#include "NTTEngineImGuiTools/NTTEngineImGuiTools.hpp"


enum ConnectionStatus
{
    UART_NONE,
    UART_OK,
    UART_FAIL_TO_OPEN,
    UART_FAIL_TO_SETTING,
    UART_FAIL_TO_TIME_SETTING,
    UART_FAIL_TO_SEND_DATA,
    UART_FAIL_TO_RECEIVE_DATA
};

enum UARTCommandType
{
    CONNECT,
    DISCONNECT,
};

union Register
{
    unsigned char buffer[2];
};

union Float32
{
    float value; 
    Register buffer[2];
};

class UARTCommand;

class UARTCom: public ntt::NTTThread
{
    public:
        UARTCom(std::string com, int baudrate = 115200);
        ~UARTCom();

        void StartConnection();
        void StopConnection();
        void RunCommand(std::shared_ptr<UARTCommand> command);

        ConnectionStatus Connect();
        ConnectionStatus SendData(std::vector<unsigned char> data, bool needRes = false);
        void Disconnect();

        ConnectionStatus ChangeCoil(unsigned char coilAddress, bool active);
        ConnectionStatus ChangeRegister(unsigned char registerAddress, Register value);
        ConnectionStatus ChangeRegisters(unsigned char startAddr, unsigned char stopAddr, std::vector<Register> data);
        ConnectionStatus ChangeFloat(unsigned char firstRegisterAddress, float value);

        ConnectionStatus GetCoil(unsigned char coilAdress, bool* active);
        ConnectionStatus GetRegister(unsigned char registerAddress, Register* value);
        ConnectionStatus GetRegisters(unsigned char startAddr, std::vector<Register*> values);
        ConnectionStatus GetFloat(unsigned char firstRegisterAddress, float* value);

        void SetAddress(unsigned char address) { address_ = address; }

        void OnInitImpl() override;
        void OnUpdateImpl() override;
        void OnReleaseImpl() override;

        void OnImGuiRender();

        inline static void StartThread() { instance_->OnRun(); }
        inline static void StopThread() { instance_->Stop(); }

        inline static UARTCom* GetInstance() { return instance_; }
        static void Initialize(std::string com = "COM7", int baudrate = 115200);
        static void StartConnectionSta();
        static void FinishConnectionSta();
        static void SubmitCommand(std::shared_ptr<UARTCommand> command);
        static void Release();
        inline static void OnImGuiRenderSta() { instance_->OnImGuiRender(); }


    private:
        enum StateEnum
        {
            IdleState,
            ConnectingState,
            WorkingState,
        };

        enum WorkingStateEnum
        {
            Working_Idle,
            Working_Run,
        };

        std::string com_;
        int baudrate_;
        HANDLE hCom_;
        DCB serialParam_ = { 0 };
        COMMTIMEOUTS timeOut_ = { 0 };
        unsigned char address_ = 0x34;
        DWORD bytesRead;
        unsigned char buffer_[100];

        ntt::ThreadValue<bool> isConnected_;

        StateEnum state_;
        WorkingStateEnum workingState_;
        ConnectionStatus status_;

        std::queue<std::shared_ptr<UARTCommand>> commands_;

        // Function definitions
        std::shared_ptr<ntt::Storage> storage_; 

        std::shared_ptr<ntt::ThreadValue<unsigned char>> startByte_;
        std::shared_ptr<ntt::ThreadValue<unsigned char>> stopByte_;
        std::shared_ptr<ntt::ThreadValue<unsigned char>> setOneCoilFuncCode_;
        std::shared_ptr<ntt::ThreadValue<unsigned char>> setMulCoilsFuncCode_;
        std::shared_ptr<ntt::ThreadValue<unsigned char>> setOneRegisterFuncCode_;
        std::shared_ptr<ntt::ThreadValue<unsigned char>> setMulRegistersFuncCode_;

        std::shared_ptr<ntt::ThreadValue<unsigned char>> readOneCoilFuncCode_;
        std::shared_ptr<ntt::ThreadValue<unsigned char>> readMulCoilsFuncCode_;
        std::shared_ptr<ntt::ThreadValue<unsigned char>> readOneRegisterFuncCode_;
        std::shared_ptr<ntt::ThreadValue<unsigned char>> readMulRegistersFuncCode_;
        // Function definitions

        void RunWorkingState();

        std::shared_ptr<ntt::ImGuiSelectableVector<std::string>> selectableVector_;

        static UARTCom* instance_;
};
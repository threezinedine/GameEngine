#pragma once
#include <memory>
#include <queue>
#include <vector>
#include <cstdint>
#include "NTTEngineThreadSystem/NTTEngineThreadSystem.hpp"
#include "NTTEngineCore/NTTEngineCore.hpp"
#include "SerialFrameResultStatus.hpp"
#include "Storage.hpp"
#include "IConnection.hpp"


class IConnection;
class ISerialCommand;

class SerialFrameManager: public ntt::NTTThread
{
    public:
        inline static void Initialize(std::unique_ptr<IConnection> connection)
        {
            instance_ = new SerialFrameManager(std::move(connection));
        }
        inline static void Release() { if (instance_ != nullptr) delete instance_; }
        inline static void StartThread() { if ( instance_ != nullptr) instance_->OnRun(); }
        inline static void StopThread() { if ( instance_ != nullptr) instance_->Stop(); }

        inline static void SubmitCommand(std::shared_ptr<ISerialCommand> command) 
        { 
            if ( instance_ != nullptr) instance_->SubmitCommandInstance(command); 
        }
        inline static void OnImGuiRender(ntt::Timestep ts) 
        { 
            if ( instance_ != nullptr) instance_->OnImGuiRenderInstance(ts); 
        }

        SerialFrameResult SendData(std::vector<uint8_t> data, std::vector<uint8_t>& res);

    protected:
        SerialFrameManager(std::unique_ptr<IConnection> connection);
        ~SerialFrameManager();

        void SubmitCommandInstance(std::shared_ptr<ISerialCommand> command);
        void OnImGuiRenderInstance(ntt::Timestep ts);

        SerialFrameResult Connect();
        void Disconnect();

        void OnInitImpl() override;
        void OnUpdateImpl() override;
        void OnReleaseImpl() override;
        
    private:
        std::unique_ptr<IConnection> connection_;
        std::queue<std::shared_ptr<ISerialCommand>> commandQueue_;

        std::shared_ptr<ntt::Storage> storage_; 
        std::shared_ptr<ntt::ThreadValue<uint8_t>> address_;
        std::shared_ptr<ntt::ThreadValue<uint8_t>> startByte_;
        std::shared_ptr<ntt::ThreadValue<uint8_t>> stopByte_;
        std::shared_ptr<ntt::ThreadValue<uint8_t>> setOneCoilFuncCode_;
        std::shared_ptr<ntt::ThreadValue<uint8_t>> setMulCoilsFuncCode_;
        std::shared_ptr<ntt::ThreadValue<uint8_t>> setOneRegisterFuncCode_;
        std::shared_ptr<ntt::ThreadValue<uint8_t>> setMulRegistersFuncCode_;

        std::shared_ptr<ntt::ThreadValue<uint8_t>> readOneCoilFuncCode_;
        std::shared_ptr<ntt::ThreadValue<uint8_t>> readMulCoilsFuncCode_;
        std::shared_ptr<ntt::ThreadValue<uint8_t>> readOneRegisterFuncCode_;
        std::shared_ptr<ntt::ThreadValue<uint8_t>> readMulRegistersFuncCode_;

        std::shared_ptr<ntt::ThreadValue<bool>> frameSettingOpen_;
        std::shared_ptr<ntt::ThreadValue<bool>> connectionSettingOpen_;

        enum StateEnum
        {
            IdleState,
            WorkingState,
        };

        enum WorkingStateEnum
        {
            Working_Idle,
            Working_Run,
        };

        StateEnum state_;
        WorkingStateEnum workingState_;

        void RunWorkingState();

        // Start static attributes
        static SerialFrameManager* instance_;
};

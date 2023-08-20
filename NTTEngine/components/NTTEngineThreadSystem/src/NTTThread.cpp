#include "NTTEngineThreadingSystem/NTTEngineThreadingSystem.hpp"


namespace ntt
{
    NTTThread::NTTThread()
    {

    }

    NTTThread::~NTTThread()
    {

    }

    void NTTThread::OnInit()
    {
        OnInitImpl();
    }

    void NTTThread::OnRun()
    {
        thread_ = std::thread(&NTTThread::OnRunImpl, this);
        isRunning_.store(true, std::memory_order_relaxed);
    }

    void NTTThread::OnRelease()
    {
        OnReleaseImpl();
    }

    void NTTThread::OnRunImpl()
    {
        while (isRunning_.load(std::memory_order_relaxed))
        {
            OnUpdateImpl();
        }
    }

    void NTTThread::Stop()
    {
        isRunning_.store(false, std::memory_order_relaxed);
        thread_.join();
        OnRelease();
    }
} // namespace ntt

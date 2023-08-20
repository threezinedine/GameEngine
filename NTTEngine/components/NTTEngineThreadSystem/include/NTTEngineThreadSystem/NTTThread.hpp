#pragma once
#include <thread>
#include <atomic>


namespace ntt
{
    class NTTThread
    {
        public:
            NTTThread();
            ~NTTThread();

            void OnInit();
            void OnRun();
            void OnRunImpl();
            void Stop();
            void OnRelease();

            virtual void OnInitImpl() = 0;
            virtual void OnUpdateImpl() = 0;
            virtual void OnReleaseImpl() = 0;

        private:
            std::atomic<bool> isRunning_;
            std::thread thread_;
    }; 
} // namespace ntt

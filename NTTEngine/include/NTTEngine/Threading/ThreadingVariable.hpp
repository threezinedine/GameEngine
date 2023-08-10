#pragma once
#include <mutex>


namespace ntt
{
    template<typename T>
    class ThreadingVariable
    {
        public:
            inline void Bind() { m_.lock(); }
            inline void UnBind() { m_.unlock(); }

            virtual T* GetPointer() = 0;
        private:
            std::mutex m_;
    }; 
} // namespace ntt

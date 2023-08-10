#pragma once
#include <mutex>


namespace ntt
{
    template<typename T>
    class ThreadingVariable
    {
        public:
            ThreadingVariable(T minValue, T maxValue)
                : minValue_(minValue), maxValue_(maxValue)
            {

            }

            inline void Bind() { m_.lock(); }
            inline void UnBind() { m_.unlock(); }

            inline const T& GetMinValue() const { return minValue_; }
            inline const T& GetMaxValue() const { return maxValue_; }

            virtual T* GetPointer() = 0;
        private:
            T minValue_;
            T maxValue_;
            std::mutex m_;
    }; 
} // namespace ntt

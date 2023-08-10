#pragma once
#include <mutex>
#include "ThreadingVariable.hpp"


namespace ntt
{
    template <typename T>
    class ThreadArray: public ThreadingVariable
    {
        public:
            ThreadArray(T* arr, T minValue, T maxValue)
                : ThreadingVariable<T>(minValue, maxValue), arr_(arr)
            {

            }

            ~ThreadArray()
            {
                if (arr_ != nullptr)
                {
                    delete arr_;
                }
            }

            inline T* GetPointer() override { return arr_; }

        private:
            T* arr_;
            std::mutex arrMutex_;
    };
} // namespace ntt

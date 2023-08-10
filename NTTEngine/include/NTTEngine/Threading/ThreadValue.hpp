#pragma once
#include <mutex>
#include "ThreadingVariable.hpp"


namespace ntt
{
    template <typename T>
    class ThreadValue: public ThreadingVariable
    {
        public:
            ThreadValue(T defaultValue)
                : value_(defaultValue)
            {

            }

            ~ThreadValue()
            {

            }

            inline T* GetPointer() override { return &value_; }

        private:
            T value_;
    };
} // namespace ntt

#pragma once
#include <mutex>
#include "ThreadingVariable.hpp"


namespace ntt
{
    template <typename T>
    class ThreadArray: public ThreadingVariable<T>
    {
        public:
            ThreadArray(T* arr, T minValue, T maxValue)
                : ThreadingVariable<T>(minValue, maxValue), arr_(arr)
            {

            }

            ThreadArray(std::vector<T> arr, T minValue, T maxValue)
                : ThreadingVariable<T>(minValue, maxValue)
            {
                arr_ = new T[arr.size()];

                for (int i=0; i<arr.size(); i++)
                {
                    arr_[i] = arr[i];
                }
            }

            std::vector<T> GetVector(int size)
            {
                return std::vector<T> (arr_, arr_ + size);
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

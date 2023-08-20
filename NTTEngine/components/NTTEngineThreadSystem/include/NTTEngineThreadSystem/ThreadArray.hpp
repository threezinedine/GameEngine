#pragma once
#include <vector>
#include <mutex>
#include "NTTEngineLog/NTTEngineLog.hpp"
#include "ThreadVariable.hpp"


namespace ntt
{
    template <typename T>
    class ThreadArray: public ThreadingVariable<T>
    {
        public:
            ThreadArray(T* arr, T minValue, T maxValue)
                : ThreadArray(arr, minValue, maxValue, nullptr, "")
            {

            }

            ThreadArray(T* arr)
                : ThreadArray(arr, arr[0], arr[0], nullptr, "")
            {

            }

            ThreadArray(T* arr, std::shared_ptr<Storage> storage, std::string key)
                : ThreadArray(arr, arr[0], arr[0], storage, key)
            {

            }

            ThreadArray(T* arr, T minValue, T maxValue,
                    std::shared_ptr<Storage> storage, std::string key)
                : ThreadingVariable<T>(minValue, maxValue, storage, key)
            {
                size_ = sizeof(arr) / sizeof(T);
                if (storage != nullptr)
                {
                    ConvertVectorToArr(
                        storage->GetValue<std::vector<T>>(key, std::vector<T>(arr, arr + size_))
                    );
                }
                else 
                {
                    arr_ = arr;
                }
            }


            ThreadArray(std::vector<T> arr, T minValue, T maxValue)
                : ThreadArray(arr, minValue, maxValue, nullptr, "")
            {

            }

            ThreadArray(std::vector<T> arr)
                : ThreadArray(arr, arr[0], arr[0], nullptr, "")
            {

            }

            ThreadArray(std::vector<T> arr, std::shared_ptr<Storage> storage, std::string key)
                : ThreadArray(arr, arr[0], arr[0], storage, key)
            {

            }

            ThreadArray(std::vector<T> arr, T minValue, T maxValue,
                    std::shared_ptr<Storage> storage, std::string key)
                : ThreadingVariable<T>(minValue, maxValue, storage, key)
            {
                size_ = arr.size();
                if (storage != nullptr)
                {
                    ConvertVectorToArr(
                        storage->GetValue<std::vector<T>>(key, arr)
                    );
                }
                else 
                {
                    ConvertVectorToArr(arr);
                }
            }

            std::vector<T> GetVector()
            {
                return std::vector<T> (arr_, arr_ + size_);
            }

            ~ThreadArray()
            {
                if (arr_ != nullptr)
                {
                    delete arr_;
                }
                Save();
            }

            void Save()
            {
                if (this->storage_ != nullptr)
                {
                    this->storage_->template SetValue<std::vector<T>>(this->key_, GetVector());
                }
            }

            inline T* GetPointer() override { return arr_; }

        private:
            T* arr_;
            int size_;
            std::mutex arrMutex_;

            void ConvertVectorToArr(std::vector<T> vec)
            {
                arr_ = new T[vec.size()];

                for (int i=0; i<vec.size(); i++)
                {
                    arr_[i] = vec[i];
                }
            }
    };
} // namespace ntt

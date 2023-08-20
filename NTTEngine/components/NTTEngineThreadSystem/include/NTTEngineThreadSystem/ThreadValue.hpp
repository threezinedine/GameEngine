#pragma once
#include <mutex>
#include "Storage.hpp"
#include "ThreadVariable.hpp"


namespace ntt
{
    template <typename T>
    class ThreadValue: public ThreadingVariable<T>
    {
        public:
            ThreadValue(T defaultValue, T minValue, T maxValue, 
                        std::shared_ptr<Storage> storage,
                        std::string key)
                : ThreadingVariable<T>(minValue, maxValue, storage, key)
            {
                if (storage != nullptr)
                {
                    value_ = storage->GetValue<T>(key, defaultValue);
                }
                else 
                {
                    value_ = defaultValue;
                }
            }

            ThreadValue(T defaultValue, T minValue, T maxValue)
                : ThreadValue(defaultValue, minValue, maxValue, nullptr, "")
            {

            }

            ThreadValue(T defaultValue, std::shared_ptr<Storage> storage,
                        std::string key)
                : ThreadValue(defaultValue, defaultValue, defaultValue, storage, key)
            {

            }

            ThreadValue(T defaultValue)
                : ThreadValue(defaultValue, defaultValue, defaultValue, nullptr, "")
            {

            }

            virtual ~ThreadValue() override
            {
                Save();
            }

            void Save()
            {
                if (this->storage_ != nullptr)
                {
                    this->storage_->template SetValue<T>(this->key_, value_);
                }
            }

            inline T* GetPointer() override { return &value_; }
            inline T GetValue() { return value_; }

        private:
            T value_;
    };
} // namespace ntt

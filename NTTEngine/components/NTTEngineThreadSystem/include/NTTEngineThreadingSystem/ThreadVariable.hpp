#pragma once
#include <mutex>
#include <memory>
#include "Storage.hpp"


namespace ntt
{
    template<typename T>
    class ThreadingVariable
    {
        public:
            ThreadingVariable(T minValue, T maxValue, 
                    std::shared_ptr<Storage> storage,
                    std::string key)
                : minValue_(minValue), maxValue_(maxValue),
                    storage_(storage), key_(key)
            {

            }

            ThreadingVariable(T minValue, T maxValue)
                : minValue_(minValue), maxValue_(maxValue),
                    storage_(nullptr), key_("")
            {

            }

            virtual ~ThreadingVariable()
            {

            }

            void Bind() { m_.lock(); }
            void UnBind() { m_.unlock(); }

            const T& GetMinValue() const { return minValue_; }
            const T& GetMaxValue() const { return maxValue_; }

            virtual T* GetPointer() = 0;
            virtual void Save() = 0;

        protected:
            std::shared_ptr<Storage> storage_;
            std::string key_;

        private:
            T minValue_;
            T maxValue_;
            std::mutex m_;
    }; 
} // namespace ntt

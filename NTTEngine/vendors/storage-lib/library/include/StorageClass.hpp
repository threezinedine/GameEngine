#pragma once
#include <iostream>
#include <memory>
#include <string>
#include "IFileSystem.hpp"
#include "StorageValueContainer.hpp"


namespace ntt
{
    class Storage
    {
        public:
            Storage(std::shared_ptr<IFileSystem> file);

            template <typename T>
            T GetValue(std::string key, T defaultValue)
            {
                if (container_ == nullptr) return defaultValue;
                return container_->GetValue<T>(key, defaultValue);
            }

            template <typename T>
            void SetValue(std::string key, T value)
            {
                if (container_ == nullptr) return;
                container_->SetValue<T>(key, value);
            }

            void Save();

        private:
            std::shared_ptr<IFileSystem> file_;
            std::unique_ptr<StorageValueContainer> container_;
    }; 
} // namespace ntt

#pragma once
#include <string>
#include <nlohmann/json.hpp>


namespace ntt
{
    class StorageValueContainer
    {
        public:
            StorageValueContainer(std::string jsonString);

            template <typename T>
            T GetValue(std::string key, T defaultValue)
            {
                auto result = data_[key];
                try 
                {
                    return (T)result;
                }
                catch (std::exception& ex)
                {
                    return defaultValue;
                }
            }

            template <typename T>
            void SetValue(std::string key, T value)
            {
                data_[key] = value;
            }

            std::string GetJsonString()
            {
                return data_.dump();
            }

        private:
            nlohmann::json data_;
    }; 
} // namespace ntt

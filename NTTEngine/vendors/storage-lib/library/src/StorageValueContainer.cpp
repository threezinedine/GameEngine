#include <iostream>
#include "StorageValueContainer.hpp"


namespace ntt
{
    StorageValueContainer::StorageValueContainer(std::string jsonString)
    {
        data_ = nlohmann::json::parse(jsonString);
    } 
} // namespace ntt

#include <iostream>
#include "StorageClass.hpp"


namespace ntt
{
    Storage::Storage(std::shared_ptr<IFileSystem> file)
        : file_(file)
    {
        container_ = std::make_unique<StorageValueContainer>(file->Read());
    } 

    void Storage::Save()
    {
        if (container_ == nullptr) return;
        file_->Save(container_->GetJsonString());
    }
} // namespace ntt

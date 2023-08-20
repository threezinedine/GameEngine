#include "NTTEngineUtils/NTTEngineUtils.hpp"


namespace ntt
{
    NTTVec3::NTTVec3(glm::vec3 vec)
        : vec_(vec), storage_(nullptr), key_("")
    {

    }

    NTTVec3::NTTVec3(glm::vec3 vec, std::shared_ptr<Storage> storage, std::string key)
        // : vec_({ vec.x, vec.y, vec.z })
        : vec_(vec), storage_(storage), key_(key)
    {
        GetValue();
    } 

    NTTVec3::NTTVec3(std::vector<float> vec, std::shared_ptr<Storage> storage, std::string key)
        // : vec_(vec)
        : vec_(vec[0], vec[1], vec[2]), storage_(storage), key_(key)
    {
        GetValue();
    }

    void NTTVec3::GetValue()
    {
        if (storage_ != nullptr)
        {
            auto value = storage_->GetValue<std::vector<float>>(key_, GetVector());
            vec_ = glm::vec3(value[0], value[1], value[2]);
        }
    }

    NTTVec3::~NTTVec3()
    {
        Save();
    }

    std::vector<float> NTTVec3::GetVector(){
        return { vec_.x, vec_.y, vec_.z };
    }

    glm::vec3& NTTVec3::GetGlmVec3()
    {
        return vec_;
    }

    float* NTTVec3::GetFirstPointer()
    {
        return &vec_.x;
    }

    void NTTVec3::Save()
    {
        if (storage_ != nullptr)
        {
            storage_->SetValue<std::vector<float>>(key_, GetVector());
        }
    }
} // namespace ntt

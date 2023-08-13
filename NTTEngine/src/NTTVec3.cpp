#include "NTTEngine/Utils/NTTVec3.hpp"


namespace ntt
{
    NTTVec3::NTTVec3(glm::vec3 vec)
        // : vec_({ vec.x, vec.y, vec.z })
        : vec_(vec)
    {

    } 

    NTTVec3::NTTVec3(std::vector<float> vec)
        // : vec_(vec)
        : vec_(vec[0], vec[1], vec[2])
    {

    }

    NTTVec3::~NTTVec3()
    {

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
} // namespace ntt

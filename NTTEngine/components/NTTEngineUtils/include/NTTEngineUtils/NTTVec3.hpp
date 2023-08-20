#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include <string>
#include "Storage.hpp"


namespace ntt
{
    class NTTVec3
    {
        public:
            NTTVec3(glm::vec3 vec);
            NTTVec3(glm::vec3 vec, std::shared_ptr<Storage> storage, std::string key);
            NTTVec3(std::vector<float> vec, std::shared_ptr<Storage> storage, std::string key);

            ~NTTVec3();

            std::vector<float> GetVector();
            glm::vec3& GetGlmVec3();
            float* GetFirstPointer();
            void Save();

        private:
            std::shared_ptr<Storage> storage_;
            std::string key_;
            glm::vec3 vec_;

            void GetValue();
    }; 
} // namespace ntt

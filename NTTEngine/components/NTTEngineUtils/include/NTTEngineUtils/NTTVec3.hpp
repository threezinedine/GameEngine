#pragma once
#include <glm/glm.hpp>
#include <vector>


namespace ntt
{
    class NTTVec3
    {
        public:
            NTTVec3(glm::vec3 vec);
            NTTVec3(std::vector<float> vec);

            ~NTTVec3();

            std::vector<float> GetVector();
            glm::vec3& GetGlmVec3();
            float* GetFirstPointer();

        private:
            // std::vector<float> vec_;
            glm::vec3 vec_;
    }; 
} // namespace ntt

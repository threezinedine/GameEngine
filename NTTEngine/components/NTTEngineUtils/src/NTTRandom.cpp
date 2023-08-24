#include <random>

#include "NTTEngineUtils/PreInclude.hpp"
#include "NTTEngineUtils/NTTRandom.hpp"


namespace ntt
{
    float NTTRandom::NormRandom(float mean, float var, float min, float max)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<float> dist(mean, var);
        float result = dist(gen);
        if (result < min) return min;
        if (result > max) return max;
        return result;
    }

    float NTTRandom::UniformRandom(float min, float max)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dist(min, max);
        return dist(gen);
    }
} // namespace ntt

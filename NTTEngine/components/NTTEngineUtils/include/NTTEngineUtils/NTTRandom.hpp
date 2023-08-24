#pragma once


namespace ntt
{
    class NTTRandom
    {
        public:
            static float NormRandom(float norm, float var, float min, float max);
            static float UniformRandom(float min, float max);
    }; 
} // namespace ntt

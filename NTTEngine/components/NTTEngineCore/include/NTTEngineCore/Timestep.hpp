#pragma once


namespace ntt
{
    class Timestep
    {
        public:
            Timestep(float delta); 
            Timestep(int delta); 

            ~Timestep();

            float GetTime() const { return delta_; }
            float GetTimeMiliSeconds() const { return delta_ * 1000.0; }

            operator float() const { return delta_; }

        private:
            float delta_;
    };
} // namespace ntt

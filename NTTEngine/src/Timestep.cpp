#include "NTTEngine/Core/Timestep.hpp"


namespace ntt
{
    Timestep::Timestep(float delta)
        : delta_(delta)
    {

    } 

    Timestep::Timestep(int delta)
        : delta_((float)delta)
    {

    }

    Timestep::~Timestep()
    {

    }
} // namespace ntt

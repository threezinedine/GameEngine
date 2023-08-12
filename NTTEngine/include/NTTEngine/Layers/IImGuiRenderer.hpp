#pragma once
#include <string>

#include "NTTEngine/Core/Core.hpp"

namespace ntt
{
    class IImGuiRenderer
    {
        public:
            virtual void OnImGuiRender(Timestep ts) = 0;
            virtual const std::string& GetName() const = 0;
    };
} // namespace ntt

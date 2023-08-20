#pragma once
#include <string>

#include "NTTEngineCore/NTTEngineCore.hpp"

namespace ntt
{
    class IImGuiRenderer
    {
        public:
            virtual void OnImGuiRender(Timestep ts) = 0;
            virtual const std::string& GetName() const = 0;
    };
} // namespace ntt

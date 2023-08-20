#pragma once
#include "NTTEngineLayerSystem/NTTEngineLayerSystem.hpp"


namespace ntt
{
    class IImGuiApplication: public IImGuiRenderer
    {
        public:
            virtual bool IsActive() = 0;
            virtual void MenuItem() = 0;
    };
} // namespace ntt

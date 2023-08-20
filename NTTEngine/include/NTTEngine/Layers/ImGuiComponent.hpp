#pragma once
#include "NTTEngineLayerSystem/NTTEngineLayerSystem.hpp"
#include <string>


namespace ntt
{
    class ImGuiComponent: public IImGuiRenderer
    {
        public:
            ImGuiComponent(const std::string& name)
                : name_(name) {}
            virtual ~ImGuiComponent() {}

            const std::string& GetName() const { return name_; }

        private:
            std::string name_;
    }; 
} // namespace ntt

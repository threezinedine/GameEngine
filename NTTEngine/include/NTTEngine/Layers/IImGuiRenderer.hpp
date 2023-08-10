#pragma once
#include <string>


namespace ntt
{
    class IImGuiRenderer
    {
        public:
            virtual void OnImGuiRender() = 0;
            virtual const std::string& GetName() const = 0;
    };
} // namespace ntt

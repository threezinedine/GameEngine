#pragma once
#include <utility>
#include <glfw/glfw3.h>

#include <NTTEngine/IInput.hpp>


namespace ntt
{
    class WindowInput: public IInput
    {
        public:
            inline static void Initialzie() { instance_ = new WindowInput(); }
            inline static void Release() { if (instance_ != nullptr) delete instance_; }

        protected:
            std::pair<int, int> GetMousePositionImpl() override;
            bool IsButtonLeftClickedImpl() override;
            bool IsKeyPressedImpl(int key) override;
            GLFWwindow* GetWindow();
    };
} // namespace ntt

#pragma once
#include <utility>


namespace ntt
{
    class IInput
    {
        public:
            static std::pair<int, int> GetMousePosition() { return instance_->GetMousePositionImpl(); }
            static bool IsButtonLeftClicked() { return instance_->IsButtonLeftClickedImpl(); }
            static bool IsKeyPressed(int key) { return instance_->IsKeyPressedImpl(key); }

        protected:
            virtual std::pair<int, int> GetMousePositionImpl() = 0;
            virtual bool IsButtonLeftClickedImpl() = 0;
            virtual bool IsKeyPressedImpl(int key) = 0;
            static IInput* instance_;
    };

} // namespace ntt

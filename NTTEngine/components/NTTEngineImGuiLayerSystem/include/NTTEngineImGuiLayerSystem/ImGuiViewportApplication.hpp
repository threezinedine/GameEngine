#pragma once

#include <memory>
#include "ImGuiApplication.hpp"
#include "NTTEngineRenderer/NTTEngineRenderer.hpp"


namespace ntt
{
    class Timestep;

    class ImGuiViewportApplication: public ImGuiApplication
    {
        public:
            ~ImGuiViewportApplication();

            void OnImGuiRender(Timestep ts) override;

            inline void BindIn() { if (frameBuffer_ != nullptr) frameBuffer_->Bind(); }
            inline void UnBindIn() { if (frameBuffer_ != nullptr) frameBuffer_->UnBind(); }

            inline static void Init() { instance_ = new ImGuiViewportApplication(); }
            inline static void Bind() { if (instance_ != nullptr) instance_->BindIn(); }
            inline static void UnBind() { if (instance_ != nullptr) instance_->UnBindIn(); }
            inline static void Release() { if (instance_ != nullptr) delete instance_; instance_ = nullptr; }
            inline static ImGuiViewportApplication* GetInstance() { return instance_; }

        protected:
            ImGuiViewportApplication();

        private:
            std::shared_ptr<FrameBuffer> frameBuffer_;

            static ImGuiViewportApplication* instance_;
    };
} // namespace ntt

#pragma once

#include <vector>

#include "Layer.hpp"


namespace ntt
{
    class LayerStack
    {
        public:
            LayerStack();
            virtual ~LayerStack();

            void PushOverlayLayer(Layer* overlay);
            void PushLayer(Layer* layer);

            void PopOverlayLayer();
            void PopLayer();

            void OnUpdate();

            inline std::vector<Layer*>::iterator Begin() { return layers_.begin(); }
            inline std::vector<Layer*>::iterator End() { return layers_.end(); }
            inline bool HaveOverlay() const { return haveOverlay_; }
            inline Layer* GetOverlay() const { return *(layers_.end() - 1); }
            inline int GetSize() const { return layers_.size(); }

        private:
            bool haveOverlay_ = false;
            std::vector<Layer*> layers_;
            int index_;
    }; 
} // namespace ntt
 
#pragma once

#include <vector>
#include <memory>

#include "Layer.hpp"


namespace ntt
{
    class LayerStack
    {
        public:
            LayerStack();
            virtual ~LayerStack();

            void PushOverlayLayer(std::shared_ptr<Layer> overlay);
            void PushLayer(std::shared_ptr<Layer> layer);

            void PopOverlayLayer();
            void PopLayer();

            void OnUpdate();

            inline std::vector<std::shared_ptr<Layer>>::iterator Begin() { return layers_.begin(); }
            inline std::vector<std::shared_ptr<Layer>>::iterator End() { return layers_.end(); }
            inline bool HaveOverlay() const { return haveOverlay_; }
            inline std::shared_ptr<Layer> GetOverlay() const { return *(layers_.end() - 1); }
            inline int GetSize() const { return layers_.size(); }

        private:
            bool haveOverlay_ = false;
            std::vector<std::shared_ptr<Layer>> layers_;
            int index_;
    }; 
} // namespace ntt
 
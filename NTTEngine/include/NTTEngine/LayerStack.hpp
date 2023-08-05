#pragma once

#include <vector>

#include "Layer.hpp"


namespace ntt
{
    class LayerStack
    {
        public:
            LayerStack();
            ~LayerStack();

            void PushOverlayLayer(Layer* overlay);
            void PushLayer(Layer* layer);

            void PopOverlayLayer();
            void PopLayer();

            inline std::vector<Layer*>::iterator Begin() { return layers_.begin(); }
            inline std::vector<Layer*>::iterator End() { return layers_.end(); }
            inline int GetSize() const { return layers_.size(); }

        private:
            std::vector<Layer*> layers_;
            std::vector<Layer*>::iterator insertedIterator_;
    }; 
} // namespace ntt
 
#include <NTTEngine/LayerStack.hpp>
#include <NTTEngine/Core.hpp>


namespace ntt
{
    LayerStack::LayerStack()
    {
        insertedIterator_ = layers_.begin();
    } 

    LayerStack::~LayerStack()
    {
        for (auto it: layers_)
        {
            delete it;
        }
    }

    void LayerStack::PushLayer(Layer* layer)
    {
        layers_.insert(insertedIterator_, layer);
        insertedIterator_++;
    }

    void LayerStack::PushOverlayLayer(Layer* overlay)
    {
        layers_.push_back(overlay);
    }

    void LayerStack::PopLayer()
    {
        if (insertedIterator_ != layers_.begin())
        {
            // layers_.erase(insertedIterator_);
            insertedIterator_--;
        }
        else 
        {
            NTT_ENGINE_WARN("No Layer to be popped");
        }
    }

    void LayerStack::PopOverlayLayer()
    {
        layers_.pop_back();
    }
} // namespace ntt

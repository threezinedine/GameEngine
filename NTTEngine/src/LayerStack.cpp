#include <NTTEngine/LayerStack.hpp>
#include <NTTEngine/Core.hpp>


namespace ntt
{
    LayerStack::LayerStack()
        : index_(0)
    {

    } 

    LayerStack::~LayerStack()
    {
        for (auto it: layers_)
        {
            if (it != nullptr)
            {
                delete it;
            }
        }
    }

    void LayerStack::PushLayer(Layer* layer)
    {
        try 
        {
            layers_.insert(layers_.begin() + index_, layer);
        }
        catch (std::exception& ex)
        {
            NTT_ENGINE_ERROR("Error in {} --- Line: {} --- Error: {}", "LayerStack.cpp", 32, ex.what());
        }
        layer->OnAttach();
        index_++;
    }

    void LayerStack::PushOverlayLayer(Layer* overlay)
    {
        layers_.push_back(overlay);
        overlay->OnAttach();
        haveOverlay_ = true;
    }

    void LayerStack::PopLayer()
    {
        if (index_ != 0)
        {
            layers_.at(--index_)->OnDetach();
        }
        else 
        {
            NTT_ENGINE_WARN("No Layer to be popped");
        }
    }

    void LayerStack::PopOverlayLayer()
    {
        (*layers_.end() - 1)->OnDetach();
        haveOverlay_ = false;
    }

    void LayerStack::OnUpdate()
    {
        for (int i=0; i<index_; i++)
        {
            layers_.at(i)->OnUpdate();
        }
        if (haveOverlay_)
        {
            (*(layers_.end() - 1))->OnUpdate();
        }
    }
} // namespace ntt

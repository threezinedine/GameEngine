#include <imgui.h>
#include "NTTEngineLayerSystem/NTTEngineLayerSystem.hpp"


namespace ntt
{
    Layer::Layer(std::string layerName)
        : layerName_(layerName)
    {

    } 

    Layer::~Layer()
    {

    }

    void Layer::OnAttach()
    {

    }

    void Layer::OnDetach()
    {

    }

    void Layer::OnUpdate(Timestep ts)
    {

    }

    void Layer::OnImGuiRender(Timestep ts)
    {
        ImGui::Begin(GetName().c_str());
        OnImGuiRenderImpl(ts);
        ImGui::End();
    }

    DEFINE_EVENT_LAYER(WindowClose)
    DEFINE_EVENT_LAYER(WindowResize)

    DEFINE_EVENT_LAYER(MouseMove)
    DEFINE_EVENT_LAYER(MouseClick)
    DEFINE_EVENT_LAYER(MouseScroll)

    DEFINE_EVENT_LAYER(KeyPress)
    DEFINE_EVENT_LAYER(KeyRelease)
} // namespace ntt

#include "NTTEngineLog/NTTEngineLog.hpp"
#include "NTTEngineWindow/NTTEngineWindow.hpp"


namespace ntt
{
    Window* Window::instance_ = nullptr;

    void Window::Init(unsigned int height, unsigned int width, const std::string& title)
    {
        NTT_ENGINE_DEBUG("Start Initial Window: height - {}; width - {}; title - {}", height, width, title);
        if (instance_ == nullptr)
        {
            instance_ = new Window(height, width, title);
        }
        NTT_ENGINE_DEBUG("Finish Initial Window");
    }

    void Window::OnUpdate()
    {

    }
} // namespace ntt

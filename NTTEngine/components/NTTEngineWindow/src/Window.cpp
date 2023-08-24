#include "NTTEngineWindow/PreInclude.hpp"
#include "NTTEngineWindow/Window.hpp"


namespace ntt
{
    Window* Window::instance_ = nullptr;

    void Window::Init(unsigned int height, unsigned int width, const std::string& title)
    {
        PROFILE_SCOPE();

        if (instance_ == nullptr)
        {
            instance_ = new Window(height, width, title);
        }
    }

    void Window::OnUpdate()
    {

    }
} // namespace ntt

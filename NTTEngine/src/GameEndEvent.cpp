#include <string>

#include <NTTEngine/EventSystem/GameEndEvent.hpp>


namespace ntt
{
    GameEndEvent::GameEndEvent(std::string& message)
        : Event(ON_GAME_END), message_(message)
    {

    } 

    GameEndEvent::~GameEndEvent()
    {

    }
} // namespace ntt

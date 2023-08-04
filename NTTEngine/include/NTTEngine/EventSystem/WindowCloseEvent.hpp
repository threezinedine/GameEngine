#pragma once 

#include "Event.hpp"
#include "EventType.hpp"


namespace ntt
{
    class WindowCloseEvent: public Event
    {
        public:
            WindowCloseEvent() : Event(WINDOW_CLOSE) {}
    };
} // namespace ntt

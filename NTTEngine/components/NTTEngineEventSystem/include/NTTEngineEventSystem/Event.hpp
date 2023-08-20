#pragma once
#include <functional>
#include <string>

#include "EventType.hpp"


namespace ntt
{
    class Event
    {
        public:
            Event(EventType eventType) 
                : eventType_(eventType) {}
            virtual ~Event() = default;

            inline EventType GetEventType() const { return eventType_; }

        private:
            EventType eventType_;
    }; 
} // namespace ntt

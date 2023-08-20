#pragma once
#include <unordered_map>
#include <functional>

#include "Event.hpp"


namespace ntt
{
    class EventDispatcher
    {
        public:
            EventDispatcher();
            ~EventDispatcher();

            void AddEvent(EventType eventType, std::function<void(Event&)> callback);
            void RemoveEvent(EventType eventType);
            void Dispatch(Event& event);

        private:
            std::unordered_map<EventType, std::function<void(Event&)>> eventsMap_;
    }; 
} // namespace ntt

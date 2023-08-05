#include <iostream>
#include <functional>

#include <NTTEngine/Core.hpp>
#include <NTTEngine/EventSystem/EventType.hpp>
#include <NTTEngine/EventSystem/EventDispatcher.hpp>


namespace ntt
{
    EventDispatcher::EventDispatcher() 
    {

    }  

    EventDispatcher::~EventDispatcher() 
    {

    }

    void EventDispatcher::AddEvent(EventType eventType, std::function<void(Event&)> callback)
    {
        auto it = eventsMap_.find(eventType);

        if (it == eventsMap_.end())
        {
            eventsMap_.insert({ eventType, callback });
        }
        else 
        {
            NTT_ENGINE_WARN("Register existed event type.");
        }
    }

    void EventDispatcher::RemoveEvent(EventType eventType)
    {

        auto it = eventsMap_.find(eventType);

        if (it != eventsMap_.end())
        {
            eventsMap_.erase(eventType);
        }
        else 
        {
            NTT_ENGINE_WARN("Remove non-existed event.");
        }
    }

    void EventDispatcher::Dispatch(Event& event)
    {
        auto it = eventsMap_.find(event.GetEventType());

        if (it != eventsMap_.end())
        {
            auto callback = it->second;
            try 
            {
                callback(event);
            }
            catch (const std::exception& ex)
            {
                NTT_ENGINE_CRITICAL("Error: {}", ex.what());
            }
        }
        else 
        {
            NTT_ENGINE_WARN("Dispatch non-existed event.");
        }
    }
} // namespace ntt

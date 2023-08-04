#pragma once
#include <NTTEngine/EventSystem/EventType.hpp>
#include <NTTEngine/EventSystem/EventDispatcher.hpp>


namespace ntt
{
    class IWindow
    {
        public:
            virtual void OnUpdate() = 0;
            virtual unsigned int GetHeight() const = 0;
            virtual unsigned int GetWidth() const = 0;
            virtual bool IsClosed() = 0;

            virtual void AddEvent(EventType eventType, std::function<void(Event&)> callback)
            {
                dispatcher_.AddEvent(eventType, callback);
            }

            virtual void SetVSync(bool enabled) = 0;
            virtual bool IsSync() const = 0;

            inline EventDispatcher GetDispatcher() const { return dispatcher_; }

        protected:
            EventDispatcher dispatcher_;
    }; 
} // namespace ntt

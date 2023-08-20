#pragma once
#include <memory>

#include "NTTEngineEventSystem/NTTEngineEventSystem.hpp"
#include "NTTEngineRenderer/NTTEngineRenderer.hpp"


namespace ntt
{
    class IWindow
    {
        public:
            virtual void OnStartUpdate() = 0;
            virtual void OnUpdate() = 0;
            virtual void OnEndUpdate() = 0;
            virtual unsigned int GetHeight() const = 0;
            virtual unsigned int GetWidth() const = 0;
            virtual void SetWindowSize(unsigned int width, unsigned int heigth) = 0;
            virtual bool IsClosed() = 0;

            virtual void AddEvent(EventType eventType, std::function<void(Event&)> callback)
            {
                dispatcher_.AddEvent(eventType, callback);
            }

            virtual void SetVSync(bool enabled) = 0;
            virtual bool IsSync() const = 0;

            inline EventDispatcher GetDispatcher() const { return dispatcher_; }
            virtual void* GetWindow() = 0;

        protected:
            EventDispatcher dispatcher_;
            std::shared_ptr<GraphicsContext> context_ = nullptr;
    }; 
} // namespace ntt

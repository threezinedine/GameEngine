#pragma once

#define DEFINE_EVENT_INTEFACE(eventType) void On##eventType(Event& event); \
        virtual void On##eventType##Impl(eventType##Event& event);

#define DEFINE_EVENT_INTEFACE_LAYER(eventType) virtual void On##eventType(eventType##Event& event);

#define BIND_FUNCTION_APPLICATION(function) std::bind(&Application::function, this, std::placeholders::_1)
#define ADD_EVENT_APPLICATION(eventType) \
    window_->AddEvent(eventType, BIND_FUNCTION_APPLICATION(On##eventType))
#define DEFINE_EVENT_APPLICATION(eventType) void Application::On##eventType(Event& event) \
{ \
    eventType##Event& e = static_cast<eventType##Event&>(event); \
    for (auto it=layerStack_.End() - 1; it!=layerStack_.Begin(); it--) \
    { \
        (*it)->On##eventType(e); \
    } \
    On##eventType##Impl(e); \
} \
void Application::On##eventType##Impl(eventType##Event& event) \
{ \
    \
}

#define DEFINE_EVENT_LAYER(eventType) void Layer::On##eventType(eventType##Event& event) \
{ \
    \
}

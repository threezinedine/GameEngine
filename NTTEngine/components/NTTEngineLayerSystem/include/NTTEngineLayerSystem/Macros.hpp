#pragma once

#define DEFINE_EVENT_LAYER(eventType) void Layer::On##eventType(eventType##Event& event) \
{ \
    \
}

#define DEFINE_EVENT_INTEFACE_LAYER(eventType) virtual void On##eventType(eventType##Event& event);
#pragma once

#include "Event.hpp"
#include "EventType.hpp"


namespace ntt
{
    class MouseMoveEvent: public Event
    {
        public:
            MouseMoveEvent(int mouseX, int mouseY)
                : Event(MouseMove), 
                    mouseX_(mouseX), mouseY_(mouseY) 
            {

            }

            inline int GetMouseX() const { return mouseX_; }
            inline int GetMouseY() const { return mouseY_; }

        private:
            int mouseX_; 
            int mouseY_;
    };
} // namespace ntt

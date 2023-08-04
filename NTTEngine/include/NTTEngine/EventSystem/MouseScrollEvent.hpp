#pragma once

#include "Event.hpp"
#include "Event.hpp"


namespace ntt
{
    class MouseScrollEvent: public Event
    {
        public:
            MouseScrollEvent(int xOffset, int yOffset)
                : Event(MOUSE_SCROLL), xOffset_(xOffset),
                    yOffset_(yOffset)
            {

            }

            inline int GetXOffset() const { return xOffset_; }
            inline int GetYOffset() const { return yOffset_; }

        private:
            int xOffset_;
            int yOffset_;
    };
} // namespace ntt

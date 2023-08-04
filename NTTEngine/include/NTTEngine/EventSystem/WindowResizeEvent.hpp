#pragma once 

#include "Event.hpp"
#include "EventType.hpp"


namespace ntt
{
    class WindowResizeEvent: public Event
    {
        public:
            WindowResizeEvent(int width, int height) 
                : Event(WINDOW_RESIZE), width_(width),
                    height_(height)
            {

            }

            inline int GetWidth() const { return width_; }
            inline int GetHeight() const { return height_; }

        private:
            int width_;
            int height_;
    };
} // namespace ntt

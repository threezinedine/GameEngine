#pragma once

#include "Event.hpp"
#include "EventType.hpp"
#include "EventDefine.hpp"


namespace ntt
{
    class MouseClickEvent: public Event
    {
        public:
            MouseClickEvent(int button, int action, int mods)
                : Event(MouseClick), button_(button),
                    action_(action), mods_(mods)
            {
                
            }

            inline int GetButton() const { return button_; }
            inline int GetAction() const { return action_; }
            inline int GetMods() const { return mods_; }

        private:
            int button_;
            int action_;
            int mods_;
    }; 
} // namespace ntt

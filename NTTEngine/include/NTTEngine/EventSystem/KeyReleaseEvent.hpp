#pragma once

#include "Event.hpp"
#include "EventType.hpp"
#include "EventDefine.hpp"


namespace ntt
{
    class KeyReleaseEvent: public Event 
    {
        public:
            KeyReleaseEvent(int key, int mods)
                : Event(KeyRelease), key_(key),
                    mods_(mods)
            {

            }

            inline int GetKey() const { return key_; }
            inline int GetMods() const { return mods_; }

        private:
            int key_;
            int mods_;
    };
} // namespace ntt

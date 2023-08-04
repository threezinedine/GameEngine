#pragma once

#include "Event.hpp"
#include "EventType.hpp"
#include "EventDefine.hpp"


namespace ntt
{
    class KeyPressEvent: public Event 
    {
        public:
            KeyPressEvent(int key, int mods)
                : Event(KEY_PRESS), key_(key),
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

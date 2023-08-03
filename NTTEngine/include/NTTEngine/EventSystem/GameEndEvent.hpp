#pragma once 
#include <string>

#include "Event.hpp"


namespace ntt
{
    class GameEndEvent: public Event 
    {
        public:
            GameEndEvent(std::string& message);
            ~GameEndEvent();

            inline std::string& GetMessage() const { return message_; }

        private:
            std::string& message_;
    }; 
} // namespace ntt

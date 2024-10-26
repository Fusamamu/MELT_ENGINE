#pragma once
#include "Event.h"
#include "CRC32.h"
#include <SDL2/SDL.h>

namespace MELT
{
    class KeyPressedEvent : public Event {
    public:
        EVENT_TYPE("KeyPressedEvent")
        KeyPressedEvent(SDL_KeyCode _keyCode, int _repeatCount):
        key(_keyCode),
        repeatCount(_repeatCount)
        {
        }

//        std::string ToString() const override
//        {
//            return fmt::format("KeyPressedEvent: {} ({} repeats)", key, repeatCount);
//        }

    public:
        SDL_KeyCode key { };
        int repeatCount { 0 };
    };
}
#pragma once
#include <string>
#include <sstream>
#include "CRC32.h"

namespace MELT
{
    class Event
    {
    public:
        virtual ~Event() = default;
        bool IsHandled { false };
        virtual const std::uint32_t GetEventType() const = 0;
        virtual std::string ToString() const { return std::to_string(GetEventType()); };
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }

    #define EVENT_TYPE(event_type)                  \
        static std::uint32_t GetStaticEventType()   \
        {                                           \
            return CRC32(event_type);               \
        }                                           \
        const std::uint32_t GetEventType() const override \
        {                                           \
            return GetStaticEventType();            \
        }
}
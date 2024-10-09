#pragma once
#include <unordered_map>
#include <any>
#include "Type.h"

namespace MELT
{
    class Event
    {
    public:
        Event() = delete;
        explicit Event(EventId _eventID);

        template<typename T>
        void SetParam(EventId id, T value);

        template<typename T>
        T GetParam(EventId id);

        EventId GetType() const;
    private:
        EventId m_EventID;
        std::unordered_map<EventId, std::any> m_Data;
    };
}
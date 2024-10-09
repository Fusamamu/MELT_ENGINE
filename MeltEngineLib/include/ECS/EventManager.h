#pragma once
#include <functional>
#include <list>
#include <unordered_map>
#include "Type.h"
#include "Event.h"

namespace MELT
{
    class EventManager
    {
    public:
        void AddListener(EventId _eventID, const std::function<void(Event&)>& _listener);
        void SendEvent(Event& _event);
        void SendEvent(EventId _evenID);
    private:
        std::unordered_map<EventId, std::list<std::function<void(Event&)>>> m_Listeners;
    };
}
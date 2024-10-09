#include "ECS/EventManager.h"

namespace MELT
{
    void EventManager::AddListener(EventId _eventID, const std::function<void(Event&)>& _listener)
    {
        m_Listeners[_eventID].push_back(_listener);
    }

    void EventManager::SendEvent(Event& _event)
    {
        uint32_t _type = _event.GetType();
        for(const auto& _listener : m_Listeners[_type])
            _listener(_event);
    }

    void EventManager::SendEvent(EventId _eventID)
    {
        Event _event(_eventID);
        for(const auto& _listener : m_Listeners[_eventID])
            _listener(_event);
    }
}
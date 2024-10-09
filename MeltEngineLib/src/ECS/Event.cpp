#include "ECS/Event.h"

namespace MELT
{
    Event::Event(EventId _eventID) : m_EventID(_eventID)
    {

    }

    template<typename T>
    void Event::SetParam(EventId _eventID, T _value)
    {
        m_Data[_eventID] = _value;
    }

    template<typename T>
    T Event::GetParam(MELT::EventId _eventID)
    {
        return std::any_cast<T>(m_Data[_eventID]);
    }

    EventId Event::GetType() const
    {
        return m_EventID;
    }
}
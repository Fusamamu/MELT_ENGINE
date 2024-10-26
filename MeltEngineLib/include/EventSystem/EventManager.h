#pragma once
//#include <iostream>
//#include <vector>
//#include <memory>

#include "Core.h"

#include "EventHandler.h"
#include "EventHandlerWrapper.h"

namespace MELT
{
    using EventType = std::uint32_t;
    using EventID   = std::uint64_t;

    class EventManager
    {
    public:
        EventManager() = default;
        EventManager(const EventManager&) = delete;
        const EventManager& operator=(const EventManager&) = delete;

        void Subscribe  (EventType _eventType, std::unique_ptr<IEventHandlerWrapper>&& _handler, EventID eventId);
        void Unsubscribe(EventType _eventType, const std::string& _handlerName, EventID _eventID);

        void TriggerEvent(const Event& _event, EventID _eventID);
        void QueueEvent(std::unique_ptr<Event>&& _event, EventID _eventID);
        void DispatchEvents();

        void Shutdown();

    private:
        std::vector<std::pair<std::unique_ptr<Event>, EventID>> m_EventQueue;
        std::unordered_map<EventType, std::vector<std::unique_ptr<IEventHandlerWrapper>>> m_Subscribers;
        std::unordered_map<EventType, std::unordered_map<EventID, std::vector<std::unique_ptr<IEventHandlerWrapper>>>> m_SubscribersByEventID;
    };

    extern EventManager gEventManager;


//    template<typename T, typename... Args>
//    constexpr UniquePtr<T> MakeUniquePtr(Args&&... args)
//    {
//        return std::make_unique<T>(std::forward<Args>(args)...);
//    }

    template<typename EventType>
    inline void Subscribe(const EventHandler<EventType>& _callback, EventID _eventId = 0, const bool _unsubscribeOnSuccess = false)
    {
        std::unique_ptr<IEventHandlerWrapper> _handler = std::make_unique<EventHandlerWrapper<EventType>>(std::forward(_callback, _unsubscribeOnSuccess));
        gEventManager.Subscribe(EventType::GetStaticEventType(), std::move(_handler), _eventId);
    }

    template<typename EventType>
    inline void Unsubscribe(const EventHandler<EventType>& callback, EventID _eventID = 0)
    {
        const std::string _handlerName = callback.target_type().name();
        gEventManager.Unsubscribe(EventType::GetStaticEventType(), _handlerName, _eventID);
    }

    inline void TriggerEvent(const Event& triggeredEvent, EventID _eventID = 0)
    {
        gEventManager.TriggerEvent(triggeredEvent, _eventID);
    }

    inline void QueueEvent(std::unique_ptr<Event>&& _queuedEvent, EventID _eventID = 0)
    {
        gEventManager.QueueEvent(std::forward<std::unique_ptr<Event>>(_queuedEvent), _eventID);
    }
}
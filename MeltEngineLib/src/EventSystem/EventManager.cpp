#include "EventManager.h"

namespace MELT
{
    EventManager gEventManager;

    void EventManager::Subscribe(MELT::EventType _eventType, std::unique_ptr<IEventHandlerWrapper>&& _handler, MELT::EventID _eventID)
    {
        if(_eventID)
        {
            auto _subscribers = m_SubscribersByEventID.find(_eventType);

            if(_subscribers != m_SubscribersByEventID.end())
            {
                auto& _handlersMap = _subscribers->second;

                auto _handlers = _handlersMap.find(_eventID);
                if(_handlers != _handlersMap.end())
                {
                    _handlers->second.emplace_back(std::move(_handler));
                    return;
                }

                m_SubscribersByEventID[_eventType][_eventID].emplace_back(std::move(_handler));
            }
        }
        else
        {
            auto _subscribers = m_Subscribers.find(_eventType);
            if(_subscribers != m_Subscribers.end())
            {
                auto& _handlers = _subscribers->second;
                for(auto& _it : _handlers)
                {
                    if(_it->GetType() == _handler->GetType())
                    {
                        std::cout << "Attempting to double-register callback" << std::endl;
                        return;
                    }
                }
                _handlers.emplace_back(std::move(_handler));
            }
            else
            {
                m_Subscribers[_eventType].emplace_back(std::move(_handler));
            }
        }
    }

    void EventManager::Unsubscribe(EventType eventType, const std::string& handlerName, EventID eventId)
    {
        if (eventId) {
            auto subscribers = m_SubscribersByEventID.find(eventType);
            if (subscribers != m_SubscribersByEventID.end()) {
                auto& handlersMap = subscribers->second;
                auto handlers = handlersMap.find(eventId);
                if (handlers != handlersMap.end()) {
                    auto& callbacks = handlers->second;
                    for (auto it = callbacks.begin(); it != callbacks.end(); ++it) {
                        if (it->get()->GetType() == handlerName) {
                            it = callbacks.erase(it);
                            return;
                        }
                    }
                }
            }
        } else {
            auto handlersIt = m_Subscribers.find(eventType);
            if (handlersIt != m_Subscribers.end()) {
                auto& handlers = handlersIt->second;
                for (auto it = handlers.begin(); it != handlers.end(); ++it) {
                    if (it->get()->GetType() == handlerName) {
                        it = handlers.erase(it);
                        return;
                    }
                }
            }
        }
    }

    void EventManager::TriggerEvent(const Event& event_, EventID eventId)
    {
        for (auto& handler : m_Subscribers[event_.GetEventType()]) {
            handler->Execute(event_);
        }

        auto& handlersMap = m_SubscribersByEventID[event_.GetEventType()];
        auto handlers = handlersMap.find(eventId);
        if (handlers != handlersMap.end()) {
            auto& callbacks = handlers->second;
            for (auto it = callbacks.begin(); it != callbacks.end();) {
                auto& handler = *it;
                handler->Execute(event_);
                if (handler->IsDestroyOnSuccess()) {
                    it = callbacks.erase(it);
                } else {
                    ++it;
                }
            }
        }
    }

    void EventManager::QueueEvent(std::unique_ptr<Event>&& _event, EventID _eventID)
    {
        m_EventQueue.emplace_back(std::move(_event), _eventID);
    }

    void EventManager::DispatchEvents()
    {
        for (auto eventIt = m_EventQueue.begin(); eventIt != m_EventQueue.end();) {
            if (!eventIt->first.get()->IsHandled) {
                TriggerEvent(*eventIt->first.get(), eventIt->second);
                eventIt = m_EventQueue.erase(eventIt);
            } else {
                ++eventIt;
            }
        }
    }

    void EventManager::Shutdown()
    {
        m_Subscribers.clear();
    }
}

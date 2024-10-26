#pragma once
#include "Event.h"
#include "EventHandler.h"
#include "IEventHandlerWrapper.h"

namespace MELT
{
    template<typename EventType>
    class EventHandlerWrapper : public IEventHandlerWrapper
    {
    public:
        explicit EventHandlerWrapper(const EventHandler<EventType>& _handler):
        m_Handler(_handler),
        m_HandlerType(_handler.target_type().name())
        {

        }

    private:
        void Call(const Event& e) override
        {
            if(e.GetEventType() == EventType::GetStaticEventType())
                m_Handler(static_cast<const EventType&>(e));
        }

        [[nodiscard]] std::string GetType()     const override { return m_HandlerType; }
        [[nodiscard]] bool IsDestroyOnSuccess() const override { return m_destroyOnSuccess;}

        EventHandler<EventType> m_Handler;
        const std::string m_HandlerType;
        bool m_destroyOnSuccess { false };
    };


//    template<typename EventType>
//    class EventHandlerWrapper : public IEventHandlerWrapper {
//    public:
//        explicit EventHandlerWrapper(const EventHandler<EventType>& handler)
//                : m_handler(handler)
//                , m_handlerType(m_handler.target_type().name()) {};
//
//    private:
//        void Call(const Event& e) override
//        {
//            if (e.GetEventType() == EventType::GetStaticEventType()) {
//                m_handler(static_cast<const EventType&>(e));
//            }
//        }
//
//        std::string GetType() const override { return m_handlerType; }
//
//        EventHandler<EventType> m_handler;
//        const std::string m_handlerType;
//    };
}
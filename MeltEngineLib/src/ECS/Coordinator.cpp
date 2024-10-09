#include "ECS/Coordinator.h"

namespace MELT
{
    void Coordinator::Init()
    {
        m_ComponentManager = std::make_unique<ComponentManager>();
        m_EntityManager     = std::make_unique<EntityManager>();
        m_EventManager     = std::make_unique<EventManager>();
        m_SystemManager    = std::make_unique<SystemManager>();
    }

    Entity Coordinator::CreateEntity()
    {
        return m_EntityManager->CreateEntity();
    }

    void Coordinator::DestroyEntity(Entity _entity)
    {
        m_EntityManager   ->DestroyEntity  (_entity);
        m_ComponentManager->EntityDestroyed(_entity);
        m_SystemManager   ->EntityDestroyed(_entity);
    }

    void Coordinator::AddEventListener(EventId eventId, std::function<void(Event&)> const& listener)
    {
        m_EventManager->AddListener(eventId, listener);
    }

    void Coordinator::SendEvent(Event& event)
    {
        m_EventManager->SendEvent(event);
    }

    void Coordinator::SendEvent(EventId eventId)
    {
        m_EventManager->SendEvent(eventId);
    }
}
#include "Coordinator.h"

namespace MELT
{
    void Coordinator::Init()
    {
        m_ComponentManager = std::make_unique<ComponentManager>();
        m_EntityManager    = std::make_unique<EntityManager>();
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

    template<typename T>
    void Coordinator::RegisterComponent()
    {
        m_ComponentManager->RegisterComponent<T>();
    }

    template<typename T>
    void Coordinator::AddComponent(Entity entity, T component)
    {
        m_ComponentManager->AddComponent<T>(entity, component);

        auto signature = m_EntityManager->GetSignature(entity);
        signature.set(m_ComponentManager->GetComponentType<T>(), true);

        m_EntityManager->SetSignature          (entity, signature);
        m_SystemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    void Coordinator::RemoveComponent(Entity entity)
    {
        m_ComponentManager->RemoveComponent<T>(entity);

        auto signature = m_EntityManager->GetSignature(entity);
        signature.set(m_ComponentManager->GetComponentType<T>(), false);

        m_EntityManager->SetSignature          (entity, signature);
        m_SystemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    T& Coordinator::GetComponent(Entity entity)
    {
        return m_ComponentManager->GetComponent<T>(entity);
    }

    template<typename T>
    ComponentType Coordinator::GetComponentType()
    {
        return m_ComponentManager->GetComponentType<T>();
    }

    template<typename T>
    std::shared_ptr<T> Coordinator::RegisterSystem()
    {
        return m_SystemManager->RegisterSystem<T>();
    }

    template<typename T>
    void Coordinator::SetSystemSignature(Signature signature)
    {
        m_SystemManager->SetSignature<T>(signature);
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
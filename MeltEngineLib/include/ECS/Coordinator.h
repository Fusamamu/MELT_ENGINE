#pragma once
#include <unordered_map>
#include <memory>

#include "Type.h"
#include "Event.h"

#include "EntityManager.h"
#include "EventManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"

#include "Camera.h"
#include "Transform.h"

namespace MELT
{
    class Coordinator
    {
    public:
        Entity SelectedEntity = -1; //-1 nothing is selected.

        std::unique_ptr<ComponentManager> m_ComponentManager;
        std::unique_ptr<EntityManager>    m_EntityManager;
        std::unique_ptr<EventManager>     m_EventManager;
        std::unique_ptr<SystemManager>    m_SystemManager;

        void Init();

        Entity CreateEntity();

        void DestroyEntity(Entity _entity);

        template<typename T>
        void RegisterComponent();

        template<typename T>
        void AddComponent(Entity _entity, T _component);

        template<typename T>
        void RemoveComponent(Entity _entity);

        template<typename T>
        T& GetComponent(Entity _entity);

        template<typename T>
        ComponentType GetComponentType();

        template<typename T>
        std::shared_ptr<T> RegisterSystem();

        template<typename T>
        void SetSystemSignature(Signature _signature);

        void AddEventListener(EventId _eventID, const std::function<void(Event&)>& _listener);
        void SendEvent(Event& _event);
        void SendEvent(EventId _eventID);

    };

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
}
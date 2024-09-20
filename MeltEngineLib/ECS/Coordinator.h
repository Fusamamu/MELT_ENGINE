#pragma once
#include <unordered_map>
#include <memory>
#include "Type.h"
#include "Event.h"
#include "EntityManager.h"
#include "EventManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"

namespace MELT
{
    class Coordinator
    {
    public:
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

    private:
        std::unique_ptr<ComponentManager> m_ComponentManager;
        std::unique_ptr<EntityManager>    m_EntityManager;
        std::unique_ptr<EventManager>     m_EventManager;
        std::unique_ptr<SystemManager>    m_SystemManager;
    };
}
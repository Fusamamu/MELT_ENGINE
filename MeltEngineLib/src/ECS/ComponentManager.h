#pragma once
#include <unordered_map>
#include <memory>
#include "Type.h"
#include "ComponentArray.h"

namespace MELT
{
    class ComponentManager
    {
    public:
        template<typename T>
        void RegisterComponent();

        template<typename T>
        ComponentType GetComponentType();

        template<typename T>
        void AddComponent(Entity _entity, T _component);

        template<typename T>
        void RemoveComponent(Entity _entity);

        template<typename T>
        T& GetComponent(Entity _entity);

        void EntityDestroyed(Entity _entity);
    private:
        ComponentType m_NextComponentType;
        std::unordered_map<const char*, ComponentType> m_ComponentTypes;
        std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_ComponentArrays;

        template<typename T>
        std::shared_ptr<ComponentArray<T>> GetComponentArray();
    };

    template<typename T>
    void ComponentManager::RegisterComponent()
    {
        const char* _typename = typeid(T).name();

        assert(m_ComponentTypes.find(_typename) == m_ComponentTypes.end() && "Registering component type more than once.");

        m_ComponentTypes .emplace(_typename, m_NextComponentType);
        m_ComponentArrays.emplace(_typename, std::make_shared<ComponentArray<T>>());

        ++m_NextComponentType;
    }

    template<typename T>
    ComponentType ComponentManager::GetComponentType()
    {
        const char* _typename = typeid(T).name();

        assert(m_ComponentTypes.find(_typename) != m_ComponentTypes.end() && "Component not registered before use.");

        return m_ComponentTypes[_typename];
    }

    template<typename T>
    void ComponentManager::AddComponent(Entity _entity, T _component)
    {
        GetComponentArray<T>()->InsertData(_entity, _component);
    }

    template<typename T>
    void ComponentManager::RemoveComponent(Entity _entity)
    {
        GetComponentArray<T>()->RemoveData(_entity);
    }

    template<typename T>
    T& ComponentManager::GetComponent(Entity _entity)
    {
        return GetComponentArray<T>()->GetData(_entity);
    }

    template<typename T>
    std::shared_ptr<ComponentArray<T>> ComponentManager::GetComponentArray()
    {
        const char* typeName = typeid(T).name();

        assert(m_ComponentTypes.find(typeName) != m_ComponentTypes.end() && "Component not registered before use.");

        return std::static_pointer_cast<ComponentArray<T>>(m_ComponentArrays[typeName]);
    }
}



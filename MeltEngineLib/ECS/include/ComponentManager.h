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
}



#include "ComponentManager.h"

namespace MELT
{
//    template<typename T>
//    ComponentType ComponentManager::GetComponentType()
//    {
//        const char* _typename = typeid(T).name();
//
//        assert(m_ComponentTypes.find(_typename) != m_ComponentTypes.end() && "Component not registered before use.");
//
//        return m_ComponentTypes[_typename];
//    }
//
//    template<typename T>
//    void ComponentManager::AddComponent(Entity _entity, T _component)
//    {
//        GetComponentArray<T>()->InsertData(_entity, _component);
//    }
//
//    template<typename T>
//    void ComponentManager::RemoveComponent(Entity _entity)
//    {
//        GetComponentArray<T>()->RemoveData(_entity);
//    }
//
//    template<typename T>
//    T& ComponentManager::GetComponent(Entity _entity)
//    {
//        GetComponentArray<T>()->GetData(_entity);
//    }

    void ComponentManager::EntityDestroyed(Entity _entity)
    {
        for (auto const& pair : m_ComponentArrays)
        {
            auto const& component = pair.second;
            component->EntityDestroyed(_entity);
        }
    }

//    template<typename T>
//    std::shared_ptr<ComponentArray<T>> ComponentManager::GetComponentArray()
//    {
//        const char* typeName = typeid(T).name();
//
//        assert(m_ComponentTypes.find(typeName) != m_ComponentTypes.end() && "Component not registered before use.");
//
//        return std::static_pointer_cast<ComponentArray<T>>(m_ComponentArrays[typeName]);
//    }
}

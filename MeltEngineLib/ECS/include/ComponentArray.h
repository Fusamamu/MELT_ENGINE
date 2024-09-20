#pragma once
#include <array>
#include <unordered_map>
#include <cassert>
#include "Type.h"

namespace MELT
{
    class IComponentArray
    {
    public:
        virtual ~IComponentArray() = default;
        virtual void EntityDestroyed(Entity _entity) = 0;
    };

    template<typename T>
    class ComponentArray : public IComponentArray
    {
    public:
        T& GetData(Entity);
        void InsertData(Entity _entity, T _component);
        void RemoveData(Entity _entity);
        void EntityDestroyed(Entity _entity) override;
    private:
        std::array<T, MAX_ENTITIES> m_ComponentArray;
        std::unordered_map<Entity, std::size_t> m_EntityToIndexMap;
        std::unordered_map<std::size_t, Entity> m_IndexToEntityMap;
        std::size_t m_Size { };
    };
}
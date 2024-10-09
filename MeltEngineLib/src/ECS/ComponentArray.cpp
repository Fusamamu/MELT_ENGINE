#include "ECS/ComponentArray.h"

namespace MELT
{
//    template<typename T>
//    T& ComponentArray<T>::GetData(Entity _entity)
//    {
//        assert(m_EntityToIndexMap.find(_entity) != m_EntityToIndexMap.end() && "Retrieving non-existent component.");
//        return m_ComponentArray(m_EntityToIndexMap[_entity]);
//    }
//
//    template<typename T>
//    void ComponentArray<T>::InsertData(Entity _entity, T _component)
//    {
//        std::size_t _newIndex = m_Size;
//        m_EntityToIndexMap[_entity] = _newIndex;
//        m_IndexToEntityMap[_newIndex] = _entity;
//        m_ComponentArray[_entity] = _component;
//        m_Size++;
//    }
//
//    template<typename T>
//    void ComponentArray<T>::RemoveData(Entity _entity)
//    {
//        std::size_t _indexOfRemoveEntity = m_EntityToIndexMap[_entity];
//        std::size_t _indexOfLastElement  = m_Size - 1;
//        m_ComponentArray[_indexOfRemoveEntity] = m_ComponentArray[_indexOfLastElement];
//
//        Entity _entityOfLastElement = m_IndexToEntityMap[_indexOfLastElement];
//        m_EntityToIndexMap[_entityOfLastElement] = _indexOfRemoveEntity;
//        m_IndexToEntityMap[_indexOfRemoveEntity] = _entityOfLastElement;
//
//        m_EntityToIndexMap.erase(_entity);
//        m_IndexToEntityMap.erase(_indexOfLastElement);
//
//        --m_Size;
//    }

//    template<typename T>
//    void ComponentArray<T>::EntityDestroyed(Entity _entity)
//    {
//        if (m_EntityToIndexMap.find(_entity) != m_EntityToIndexMap.end())
//            RemoveData(_entity);
//    }
}
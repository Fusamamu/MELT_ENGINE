#include "ECS/EntityManager.h"

namespace MELT
{
    EntityManager::EntityManager()
    {
        for(Entity _i = 0; _i < MAX_ENTITIES; ++_i)
            AvailableEntities.push(_i);
    }

    Entity EntityManager::CreateEntity()
    {
        assert(LivingEntityCount < MAX_ENTITIES && "Too many entities in existence.");
        Entity _e = AvailableEntities.front();
        AvailableEntities.pop();
        ActiveEntities.push_back(_e);
        LivingEntityCount++;
        return _e;
    }

    void EntityManager::DestroyEntity(const Entity& _entity)
    {
        assert(_entity < MAX_ENTITIES && "Entity out of range");
        Signatures[_entity].reset();
        AvailableEntities.push(_entity);
        ActiveEntities.erase(std::remove(ActiveEntities.begin(), ActiveEntities.end(), _entity), ActiveEntities.begin());
        LivingEntityCount--;
    }

    void EntityManager::SetSignature(const Entity& _entity, Signature _signature)
    {
        assert(_entity < MAX_ENTITIES && "Entity out of range");
        Signatures[_entity] = _signature;
    }

    Signature EntityManager::GetSignature(const Entity& _entity)
    {
        assert(_entity < MAX_ENTITIES && "Entity out of range");
        return Signatures[_entity];
    }
}
#pragma once
#include <iostream>
#include <bitset>
#include <queue>
#include <cassert>
#include "Type.h"

namespace MELT
{
    class EntityManager
    {
    public:
        std::queue<Entity> AvailableEntities;
        std::vector<Entity> ActiveEntities;
        std::array<Signature, MAX_ENTITIES> Signatures;

        uint32_t LivingEntityCount;

        EntityManager();

        Entity CreateEntity();
        void DestroyEntity(const Entity& _entity);
        void SetSignature(const Entity& _entity, Signature _signature);
        Signature GetSignature(const Entity& _entity);
    };
}
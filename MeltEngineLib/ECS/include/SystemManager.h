#pragma once
#include <set>
#include <bitset>
#include <memory>
#include <unordered_map>
#include <cassert>
#include "Type.h"

namespace MELT
{
    class System
    {
    public:
        std::set<Entity> Entities;
    };

    class SystemManager
    {
    public:
        template<typename T>
        std::shared_ptr<T> RegisterSystem();

        template<typename T>
        void SetSignature(Signature _signature);

        void EntityDestroyed(Entity _entity);
        void EntitySignatureChanged(Entity _entity, Signature _signature);
    private:
        std::unordered_map<const char*, Signature> m_Signatures;
        std::unordered_map<const char*, std::shared_ptr<System>> m_Systems;
    };
}
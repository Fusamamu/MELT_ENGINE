#include "SystemManager.h"

namespace MELT
{
//    template<typename T>
//    std::shared_ptr<T> SystemManager::RegisterSystem()
//    {
//        const char* _typeName = typeid(T).name();
//        assert(m_Systems.find(_typeName) == m_Systems.end() && "Registering system more than once.");
//        auto _system = std::make_shared<T>();
//        m_Systems.emplace(_typeName, _system);
//        return _system;
//    }
//
//    template<typename T>
//    void SystemManager::SetSignature(Signature _signature)
//    {
//        const char* _typeName = typeid(T).name();
//        assert(m_Systems.find(_typeName) != m_Systems.end() && "System used before registered.");
//        m_Signatures.emplace(_typeName, _signature);
//    }

    void SystemManager::EntityDestroyed(Entity _entity)
    {
        for (auto const& pair : m_Systems)
        {
            auto const& system = pair.second;
            system->Entities.erase(_entity);
        }
    }

    void SystemManager::EntitySignatureChanged(Entity _entity, Signature _signature)
    {
        for (auto const& [_type, _system] : m_Systems)
        {
            auto const& _systemSignature = m_Signatures[_type];

            if ((_signature & _systemSignature) == _systemSignature)
                _system->Entities.insert(_entity);
            else
                _system->Entities.erase(_entity);
        }
    }
}
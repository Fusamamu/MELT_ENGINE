#include "ECS/SystemManager.h"

namespace MELT
{
    void SystemManager::UpdateInput()
    {
        for (auto const& [_systemName, _system] : m_Systems)
           _system->OnInputUpdate(0);
    }

    void SystemManager::Update()
    {
        for (auto const& [_systemName, _system] : m_Systems)
            _system->OnUpdate(0);
    }

    void SystemManager::UpdateRender()
    {
        for (auto const& [_systemName, _system] : m_Systems)
            _system->OnRender(0);
    }

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
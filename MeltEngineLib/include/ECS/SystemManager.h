#pragma once
#include <set>
#include <bitset>
#include <memory>
#include <unordered_map>
#include <cassert>
#include "Type.h"

namespace MELT
{
#define NATIVE_SYSTEM_OVERRIDE \
    void OnStart() override; \
    void OnInputUpdate(float _dt) override; \
    void OnUpdate(float _dt) override; \
    void OnRender(float _dt) override; \
    void OnEnd() override

    class INativeSystem
    {
    public:
        std::set<Entity> Entities;
        virtual void OnStart() = 0;
        virtual void OnInputUpdate(float _dt) = 0;
        virtual void OnUpdate(float _dt) = 0;
        virtual void OnRender(float _dt) = 0;
        virtual void OnEnd() = 0;
        virtual ~INativeSystem() = default;
    };

    class SystemManager
    {
    public:
        void UpdateInput();
        void Update();
        void UpdateRender();

        template<typename T>
        std::shared_ptr<T> RegisterSystem();

        template<typename T>
        void SetSignature(Signature _signature);

        void EntityDestroyed(Entity _entity);
        void EntitySignatureChanged(Entity _entity, Signature _signature);
    private:
        std::unordered_map<const char*, Signature> m_Signatures;
        std::unordered_map<const char*, std::shared_ptr<INativeSystem>> m_Systems;
    };

    template<typename T>
    std::shared_ptr<T> SystemManager::RegisterSystem()
    {
        const char* _typeName = typeid(T).name();
        assert(m_Systems.find(_typeName) == m_Systems.end() && "Registering system more than once.");
        auto _system = std::make_shared<T>();
        m_Systems.emplace(_typeName, _system);
        return _system;
    }

    template<typename T>
    void SystemManager::SetSignature(Signature _signature)
    {
        const char* _typeName = typeid(T).name();
        assert(m_Systems.find(_typeName) != m_Systems.end() && "System used before registered.");
        m_Signatures.emplace(_typeName, _signature);
    }
}
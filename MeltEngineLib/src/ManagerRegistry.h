#ifndef MANAGERREGISTRY_H
#define MANAGERREGISTRY_H

#include "Core.h"

class ManagerRegistry {
public:
    ManagerRegistry () = default;
    ~ManagerRegistry() = default;

    template<typename T>
    void Register(std::shared_ptr<T> manager)
    {
        std::type_index type = std::type_index(typeid(T));
        if (m_managers.count(type))
            throw std::runtime_error("Manager already registered.");
        m_managers[type] = manager;
    }

    template<typename T>
    void Replace(std::shared_ptr<T> manager) {
        m_managers[std::type_index(typeid(T))] = manager;
    }

    template<typename T>
    std::shared_ptr<T> get() const
    {
        std::type_index type = std::type_index(typeid(T));
        auto it = m_managers.find(type);
        if (it == m_managers.end())
            throw std::runtime_error("Manager not found.");
        return std::static_pointer_cast<T>(it->second);
    }

    template<typename T>
    bool Has() const
    {
        return m_managers.count(std::type_index(typeid(T))) > 0;
    }

    template<typename T>
    void Remove()
    {
        m_managers.erase(std::type_index(typeid(T)));
    }

    void Clear()
    {
        m_managers.clear();
    }
private:
    std::unordered_map<std::type_index, std::shared_ptr<void>> m_managers;
};

#endif

#include "Scene.h"

namespace MELT
{
    Node& Scene::create_node(const std::string& _name)
    {
        entt::entity _entity = ecs_registry.create();
        m_nodes.emplace_back(_name, this, _entity);
        return m_nodes.back();
    }

    void Scene::destroy_node(const Node& _node)
    {
        entt::entity entity = _node.get_entity();
        if (!ecs_registry.valid(entity))
            return;
        ecs_registry.destroy(entity);
        auto it = std::remove_if(m_nodes.begin(), m_nodes.end(), [&](const Node& node) {
            return node.get_entity() == entity;
        });
        m_nodes.erase(it, m_nodes.end());
    }

    void Scene::destroy_node_by_id(NodeID _id)
    {
        auto _it = std::find_if(m_nodes.begin(), m_nodes.end(), [&](const Node& _node)
        {
            return _node.id == _id;
        });

        if (_it != m_nodes.end())
        {
            entt::entity entity = _it->get_entity();
            if (!ecs_registry.valid(entity))
                return;
            ecs_registry.destroy(entity);

            m_nodes.erase(_it, m_nodes.end());
        }
    }
}

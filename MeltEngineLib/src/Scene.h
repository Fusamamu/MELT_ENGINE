#ifndef SCENE_H
#define SCENE_H

#include "Core.h"
#include "Node.h"

namespace MELT
{
    class Scene
    {
    public:
        bool is_active = false;

        Node* selected_node;
        std::optional<NodeID> selected_node_id;

        entt::registry ecs_registry;

        Scene()  = default;
        ~Scene() = default;

        std::vector<Node>& get_all_nodes(){ return m_nodes; }

        Node& create_node(const std::string& _name);
        void destroy_node(const Node& _node);

        template<typename T, typename... Args>
        Node& create_node_with_type(const std::string& _name, Args&&... _args)
        {
            entt::entity _entity = ecs_registry.create();
            ecs_registry.emplace<T>(_entity, std::forward<Args>(_args)...);
            m_nodes.emplace_back(_name, this, _entity);
            return m_nodes.back();
        }

        Node* get_node(const NodeID& _node_id)
        {
            for (auto& _node : m_nodes)
                if (_node.id == _node_id)
                    return &_node;
            return nullptr;
        }

        Node* get_selected_node()
        {
            if (selected_node_id.has_value())
                return get_node(selected_node_id.value());
            return nullptr;
        }

        void deselect_all_nodes()
        {
            for (auto& _node : m_nodes)
                _node.is_selected = false;
        }

        void select_all_nodes()
        {
            for (auto& _node : m_nodes)
                _node.is_selected = true;
        }
    private:
        std::vector<Node> m_nodes;
    };

    template<typename T, typename... Args>
    T& Node::add_component(Args&&... _args){
        return m_scene_owner->ecs_registry.emplace<T>(m_entity_handle, std::forward<Args>(_args)...);
    }
    template<typename T>
    void Node::remove_component() {
        m_scene_owner->ecs_registry.remove<T>(m_entity_handle);
    }
    template<typename T>
    T& Node::get_component(){
        return m_scene_owner->ecs_registry.get<T>(m_entity_handle);
    }
    template<typename T>
    bool Node::has_component() const {
        return m_scene_owner->ecs_registry.all_of<T>(m_entity_handle);
    }
}

#endif

#ifndef SCENE_H
#define SCENE_H

#include "Core.h"
#include "Node.h"

#include "UISystem.h"
#include "MovementSystem.h"
#include "NodeEditor.h"
#include "UISystem.h"

namespace MELT
{
    class Scene
    {
    public:
        std::string name = "new scene";
        std::string uuid;

        bool is_active = false;

        std::optional<NodeID> selected_node_id;

        entt::registry ecs_registry;
        UISystem       ui_system;

        Scene()
        {
            uuid = generate_uuid(reinterpret_cast<uintptr_t>(this));
        }
        ~Scene() = default;

        void init();
        void update();
        void quit();

        std::vector<Node>& get_all_nodes(){ return m_nodes; }
        [[nodiscard]] const std::vector<Node>& get_all_nodes() const { return m_nodes; }

        Node& create_node(const std::string& _name);
        void destroy_node(const Node& _node);
        void destroy_node_by_id(NodeID _id);

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

        void select_node_id(const NodeID& _node_id)
        {
            selected_node_id = _node_id;
            Node* _selected_node = resolve_node_id(_node_id);
            if (_selected_node)
                _selected_node->on_get_selected();
        }

        void select_all_nodes()
        {
            for (auto& _node : m_nodes)
                _node.on_get_selected();
        }

        void deselect_node_id(const NodeID& _node_id)
        {
            selected_node_id.reset();
            Node* _selected_node = resolve_node_id(_node_id);
            if (_selected_node)
                _selected_node->on_get_deselected();
        }

        void deselect_all_nodes()
        {
            if (selected_node_id.has_value())
            {
                Node* _selected_node = resolve_node_id(selected_node_id.value());
                if (_selected_node)
                    _selected_node->on_get_deselected();
                selected_node_id.reset();
            }

            for (auto& _node : m_nodes)
                _node.on_get_deselected();
        }

        Node* resolve_node_id(const NodeID& _node_id)
        {
            for (auto& _node : m_nodes)
                if (_node.id == _node_id)
                    return &_node;
            return nullptr;
        }

        template<typename T>
        bool try_get_first(T& _component)
        {
            auto _view = ecs_registry.view<T>();
            for (auto entity : _view)
            {
                _component = _view.get(entity);
                return true;
            }
            return false;
        }
    private:
        std::vector<Node> m_nodes;

        MovementSystem m_movement_system;
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
    T* Node::try_get_component() {
        return m_scene_owner->ecs_registry.try_get<T>(m_entity_handle);
    }

    template<typename T>
    bool Node::has_component() const {
        return m_scene_owner->ecs_registry.all_of<T>(m_entity_handle);
    }
}

#endif

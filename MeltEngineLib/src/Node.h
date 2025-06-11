#pragma once
#include "Core.h"
#include "Type.h"

namespace MELT
{
    using NodeID = std::string;

    class Scene;

    class Node
    {
    public:
        NodeID id;
        std::string name;

        bool is_selected;

        Node(const std::string& _name, Scene* _scene_owner, entt::entity _entity);
        Node(std::string _name, M_VEC3 _position);
        Node();
        ~Node();

        [[nodiscard]]
        entt::entity get_entity() const {
            return m_entity_handle;
        }

        void add_child   (const NodeID& _node_id);
        void remove_child(const NodeID& _node_id);

        bool has_parent() const;
        NodeID get_parent() const;
        std::vector<NodeID> get_children() const;

        template<typename T, typename... Args>
        T& add_component(Args&&... _args);

        template<typename T>
        void remove_component();

        template<typename T>
        T& get_component();

        template<typename T>
        T* try_get_component();

        template<typename T>
        bool has_component() const;

        explicit operator bool() const { return m_entity_handle != entt::null; }
    private:
        Scene* m_scene_owner;
        entt::entity m_entity_handle;

        NodeID m_parent = "n/a";
        std::vector<NodeID> m_children;
    };

    //#include "Node.inl"
}
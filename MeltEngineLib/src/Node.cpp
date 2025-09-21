#include "Node.h"

#include <Scene.h>

namespace MELT
{
    SceneNode::SceneNode(const std::string& _name, Scene* _scene_owner, entt::entity _entity):
        name(_name),
        m_scene_owner(_scene_owner),
        m_entity_handle(_entity),
        is_selected(false)
    {
        id = generate_uuid(reinterpret_cast<uintptr_t>(this));
    }

    SceneNode::SceneNode(std::string _name, M_VEC3 _position):
        name(_name),
        is_selected(false),
        m_scene_owner(nullptr)
    {
        id = generate_uuid(reinterpret_cast<uintptr_t>(this));
    }

    SceneNode::SceneNode()  = default;
    SceneNode::~SceneNode() = default;

    void SceneNode::add_child(const NodeID& _node_id)
    {
        SceneNode* _node = m_scene_owner->resolve_node_id(_node_id);

        if (_node->has_parent())
        {
            NodeID _parent_id = _node->get_parent();
            SceneNode* _parent_node = m_scene_owner->resolve_node_id(_parent_id);
            _parent_node->remove_child(_node_id);
        }

        _node->m_parent = id;

        m_children.push_back(_node_id);
    }

    void SceneNode::remove_child(const NodeID& _node_id)
    {
        m_children.erase(std::remove(m_children.begin(), m_children.end(), _node_id), m_children.end());
    }

    bool SceneNode::has_parent() const
    {
        return m_parent != "n/a";
    }

    NodeID SceneNode::get_parent() const
    {
        return m_parent;
    }

    std::vector<NodeID> SceneNode::get_children() const
    {
        return m_children;
    }

    void SceneNode::on_get_selected()
    {
        is_selected = true;
        NodeEditor& _node_editor = m_scene_owner->ecs_registry.get<NodeEditor>(m_entity_handle);
        _node_editor.is_selected = true;
    }

    void SceneNode::on_get_deselected()
    {
        is_selected = false;
        NodeEditor& _node_editor = m_scene_owner->ecs_registry.get<NodeEditor>(m_entity_handle);
        _node_editor.is_selected = false;
    }
}

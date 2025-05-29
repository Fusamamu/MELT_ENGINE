#include "Node.h"

namespace MELT
{
    Node::Node(const std::string& _name, Scene* _scene_owner, entt::entity _entity):
        name(_name),
        m_scene_owner(_scene_owner),
        m_entity_handle(_entity),
        isSelected(false)
    {
        id = GenerateUUID(reinterpret_cast<uintptr_t>(this));
    }

    Node::Node(std::string _name, M_VEC3 _position):
        name(_name),
        position(_position),
        isSelected(false),
        m_scene_owner(nullptr)
    {
        id = GenerateUUID(reinterpret_cast<uintptr_t>(this));
    }

    Node::Node()  = default;
    Node::~Node() = default;
}
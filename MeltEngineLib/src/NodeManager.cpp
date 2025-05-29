#include "NodeManager.h"

namespace MELT
{
    NodeManager::NodeManager () = default;
    NodeManager::~NodeManager() = default;

    Node& NodeManager::CreateNode(M_MATH::vec2<float> _at_position)
    {
        Node _newNode ("new node", _at_position);
        SceneNodes.push_back(std::move(_newNode));
        return SceneNodes.back();
    }
}
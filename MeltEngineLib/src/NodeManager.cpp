#include "NodeManager.h"

namespace MELT
{
    NodeManager::NodeManager () = default;
    NodeManager::~NodeManager() = default;

    Node& NodeManager::create_node(glm::vec3 _at_position)
    {
        Node _newNode ("new node", _at_position);
        SceneNodes.push_back(std::move(_newNode));
        return SceneNodes.back();
    }
}
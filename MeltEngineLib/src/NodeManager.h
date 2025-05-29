#pragma once
#include "Core.h"
#include "Node.h"

namespace MELT
{
    class NodeManager
    {
    public:

        Node* CurrentSelectedNode;
        std::vector<Node> SceneNodes;

        NodeManager();
        ~NodeManager();

        Node& create_node(glm::vec3 _at_position);
    };
}
#pragma once
#include "Core.h"
#include "Node.h"
#include "Vector.h"

namespace MELT
{
    class NodeManager
    {
    public:

        Node* CurrentSelectedNode;

        std::vector<Node> SceneNodes;

        Node& CreateNode(MELT::vec2<float> _atPosition);

        //void SelectNode(Node* _node);
    };
}
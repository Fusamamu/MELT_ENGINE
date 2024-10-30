#pragma once
#include "Core.h"
#include "Node.h"
#include "Vector.h"
#include "InputSystem.h"

namespace MELT
{
    class NodeManager
    {
    public:

        Node* CurrentSelectedNode;

        std::vector<Node> SceneNodes;

        Node& CreateNode(M_MATH::vec2<float> _atPosition);

        //void SelectNode(Node* _node);
    };
}
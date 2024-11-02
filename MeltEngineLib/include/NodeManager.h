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

        bool LoclSelectedNode;

        std::vector<Node> SceneNodes;

        NodeManager();
        ~NodeManager();

        Node& CreateNode(M_MATH::vec2<float> _atPosition);

        //void SelectNode(Node* _node);
    };
}
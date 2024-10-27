#include "NodeManager.h"

namespace MELT
{
    Node& NodeManager::CreateNode(MELT::vec2<float> _atPosition)
    {
        Node _newNode ("new node", _atPosition);
        SceneNodes.push_back(std::move(_newNode));
        return SceneNodes.back();
    }

//    void NodeManager::SelectNode(MELT::Node* _node)
//    {
//        CurrentSelectedNode = _node;
//    }
}
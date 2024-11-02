#include "NodeManager.h"

namespace MELT
{
    NodeManager::NodeManager(): LoclSelectedNode(false)
    {

    }

    NodeManager::~NodeManager()
    {

    }

    Node& NodeManager::CreateNode(M_MATH::vec2<float> _atPosition)
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
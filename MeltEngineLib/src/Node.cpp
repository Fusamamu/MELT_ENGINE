#include "Node.h"

namespace MELT
{
    Node::Node(std::string _name, MELT::vec2<float> _position): name(_name), position(_position), isSelected(false)
    {
        id = MELT::GenerateUUID(reinterpret_cast<uintptr_t>(this));
    }

    Node::~Node()
    {

    }
}
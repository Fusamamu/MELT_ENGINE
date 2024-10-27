#pragma once
#include "Core.h"
#include "Vector.h"
#include "Type.h"

namespace MELT
{
    using NodeID = std::string;

    struct Node
    {
        NodeID id;
        std::string name;
        bool isSelected;
        MELT::vec2<float> position;

        MELT::Entity entityRef;

        Node(std::string _name, MELT::vec2<float> _position);
        ~Node();
    };
}
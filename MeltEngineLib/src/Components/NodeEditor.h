#ifndef NODEEDITOR_H
#define NODEEDITOR_H

#include "Core.h"
#include "Node.h"

namespace MELT
{
    struct NodeEditor
    {
        NodeID id;
        bool is_selected = false;
        NodeEditor() = default;
        ~NodeEditor() = default;
    };

}

#endif //NODEEDITOR_H

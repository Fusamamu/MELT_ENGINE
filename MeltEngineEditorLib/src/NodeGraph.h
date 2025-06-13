#ifndef NODEGRAPH_H
#define NODEGRAPH_H

#include "EditorCore.h"

namespace MELT_EDITOR
{
    class Editor;

    class NodeGraph
    {
    public:
        bool is_open;
        NodeGraph()  = default;
        ~NodeGraph() = default;
        void init(Editor* _editor);
        void draw_gui();
    private:
        Editor*       m_editor;
        MELT::Engine* m_engine;
    };
}

#endif

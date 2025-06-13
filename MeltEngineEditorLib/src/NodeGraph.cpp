#include "NodeGraph.h"
#include "MeltEngineEditor.h"

namespace MELT_EDITOR
{
    void NodeGraph::init(Editor* _editor)
    {
        m_editor = _editor;
        m_engine = _editor->engine;
    }

    void NodeGraph::draw_gui()
    {

    }
}
#ifndef HIERARCHYGUI_H
#define HIERARCHYGUI_H

namespace MELT_EDITOR
{
    class Editor;

    class HierarchyGUI
    {
    public:
        HierarchyGUI();
        void init(Editor* _editor);
        void draw_gui();
        void draw_node(MELT::Node& _node);
    private:
        Editor*       m_editor;
        MELT::Engine* m_engine;

        int _selectedItem = -1;
    };

}

#endif //HIERARCHYGUI_H

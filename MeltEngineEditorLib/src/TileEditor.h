#ifndef SYSTEM_GUI_H
#define SYSTEM_GUI_H

namespace MELT_EDITOR
{
    class Editor;

    class TileEditor
    {
    public:
        TileEditor();
        void init(Editor* _editor);
        void draw_gui();
    private:
        Editor*       m_editor;
        MELT::Engine* m_engine;

        int column = 10;
        int row    = 10;
        int height = 1;

        std::vector<MELT::NodeID> tile_ids;
    };
}

#endif

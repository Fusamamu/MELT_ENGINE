#ifndef SCENEVIEWGUI_H
#define SCENEVIEWGUI_H

namespace MELT_EDITOR
{
    class Editor;

    class SceneViewGUI
    {
    public:
        SceneViewGUI();
        void init(Editor* _editor);
        void draw_gui();
    private:
        Editor*       m_editor;
        MELT::Engine* m_engine;
    };
}

#endif //SCENEVIEWGUI_H

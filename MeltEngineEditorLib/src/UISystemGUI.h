#ifndef UISYSTEM_GUI
#define UISYSTEM_GUI

#include "GUI.h"
#include "AssetRegistry.h"
#include "UISystem.h"
#include "UI.h"

namespace MELT_EDITOR
{
    class Editor;

    class UISystemGUI
    {
    public:
        UISystemGUI();
        void init(Editor* _editor);
        void draw_gui();
    private:
        Editor*       m_editor;
        MELT::Engine* m_engine;
    };
}

#endif

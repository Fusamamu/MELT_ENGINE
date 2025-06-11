#pragma once

namespace MELT_EDITOR
{
    class Editor;

    class ConsoleGUI
    {
    public:
        Editor* EditorOwner;
        ConsoleGUI();
        void draw_gui();
    };
}
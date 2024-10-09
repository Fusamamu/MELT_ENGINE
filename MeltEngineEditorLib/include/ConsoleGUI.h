#pragma once
#include <string>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

namespace MELT_EDITOR
{
    class Editor;

    class ConsoleGUI
    {
    public:
        Editor* EditorOwner;
        ConsoleGUI();
        void DrawGUI();
    };
}
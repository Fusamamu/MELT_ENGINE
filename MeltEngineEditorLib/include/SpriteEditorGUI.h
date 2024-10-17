#pragma once
#include <string>
#include <vector>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

namespace MELT_EDITOR
{
    class Editor;

    struct SpriteData
    {
        ImVec2 Position;
        ImVec2 Size;
    };

    class SpriteEditorGUI
    {
    public:
        bool IsOpened;

        ImVec2 GridSize;
        ImVec2 CellSize;

        std::vector<SpriteData> CachedSpriteData;

        Editor* EditorOwner;
        SpriteEditorGUI();

        void Open();
        void Close();
        void DrawGUI();
    };
}
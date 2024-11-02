#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#include "TextureManager.h"

namespace MELT_EDITOR
{
    class Editor;

    class SpriteEditorGUI
    {
    public:
        bool IsOpened;

        MELT::TextureData* EditTextureData;

        ImVec2 GridSize;
        ImVec2 CellSize;

        std::vector<MELT::SpriteData> CachedSpriteData;

        Editor* EditorOwner;
        SpriteEditorGUI();

        void Init();
        void GenerateSpriteByGridSetting();
        void Open();
        void Close();
        void DrawGUI();
    };
}
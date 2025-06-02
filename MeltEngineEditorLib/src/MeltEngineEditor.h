#pragma once

// #include <cstdio>
// #include <iostream>
// #include <string>
// #include <fstream>
// #include <sstream>
// #include <vector>
// #include <functional>
// #include <filesystem>
// #include <unordered_map>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "ImGuizmo.h"

#include "IconsKenney.h"

#include "MeltEngine.h"

#include "ApplicationState.h"
#include "SpriteEditorGUI.h"
#include "ScriptEditorGUI.h"
#include "ConsoleGUI.h"

#include "nfd.h"

namespace MELT_EDITOR
{
    class Editor
    {   
    public:
        MELT::Engine* engine;

        std::vector<std::string> fileNames;

        std::filesystem::path CurrentWorkingProjectRootPath;

        SpriteEditorGUI SpriteEditorGUI;
        ScriptEditorGUI ScriptEditorGUI;
        ConsoleGUI      ConsoleGUI;

        bool SpriteEditorDisplayed;

        ApplicationModeManager application_mode_manager;

        explicit Editor();
        ~Editor();

        void init();
        void update();
        void update_input(SDL_Event _event);
        void update_gui();
        void quit();

        void GetContent();

        void draw_main_menubar       ();
        void draw_scene_view_gui     ();
        void draw_gameplay_view_gui  ();
        void draw_hierarchy_gui      ();
        void draw_inspector_gui      ();
        void draw_material_gui       ();
        void draw_assets_gui         ();
        void draw_content_gui        ();
        void draw_render_pipeline_gui();

        void DrawLineSeparator();

        void DrawTransformComponentPanel  (MELT::Transform   & _transform  );
        void DrawRendererComponentPanel   (MELT::MeshRenderer& _renderer   );
        void DrawBoxColliderComponentPanel(MELT::BoxCollider & _boxCollider);

        void DrawSpriteRendererComponentPanel(MELT::SpriteRenderer& _spriteRenderer);

        std::string CurrentTextDisplay;
        std::string LoadTextFile(const std::string& _filePath);

        std::unordered_map<MELT::Entity, bool> Entities;

        std::vector<std::string> Components;

        const char* PROJECT_SETTING_PATH = "../Project/ProjectSettings.yaml";
        const char* SCENE_PATH           = "../Project/Scene.yaml";

        void SaveScene();
        void TestSave();

        const ImU32 BackgroundColor;

        void DrawSprite(const MELT::TextureData_old& _textureData, ImVec2 _position, ImVec2 _spriteSize, ImVec2 _spritePosition);
        void DrawSpriteWithDrawList(ImTextureID texture_id, ImVec2 position, ImVec2 sprite_size, ImVec2 sprite_position);

    private:
        bool m_is_running = true;


    };
}

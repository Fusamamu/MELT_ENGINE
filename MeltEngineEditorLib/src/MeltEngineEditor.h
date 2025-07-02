#pragma once

#include "EditorCore.h"

#include "ApplicationState.h"
#include "SpriteEditorGUI.h"
#include "ScriptEditorGUI.h"
#include "ConsoleGUI.h"
#include "ProjectGUI.h"
#include "HierarchyGUI.h"
#include "InspectorGUI.h"
#include "NodeGraph.h"
#include "TileEditor.h"
#include "SceneViewGUI.h"
#include "Material.h"

namespace MELT_EDITOR
{
    enum class InspectorSelectionType
    {
        NONE,
        ENTITY_NODE,
        MATERIAL
    };

    struct InspectorSelectionContext
    {
        InspectorSelectionType type = InspectorSelectionType::NONE;
        UUID selected_uuid;
    };

    class Editor
    {   
    public:
        bool is_running = true;

        MELT::Engine* engine;

        std::vector<std::string> fileNames;

        std::filesystem::path working_project_directory = "../Project";

        InspectorSelectionContext inspector_selection_context;

        SceneViewGUI    scene_view_gui;
        SpriteEditorGUI sprite_editor_gui;
        ScriptEditorGUI script_editor_gui;
        ConsoleGUI      console_gui;
        ProjectGUI      project_gui;
        HierarchyGUI    hierarchy_gui;
        NodeGraph       node_graph_gui;
        InspectorGUI    inspector_gui;
        TileEditor      system_gui;

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
        void draw_gameplay_view_gui  ();
        void draw_material_gui       ();
        void draw_content_gui        ();
        void draw_render_pipeline_gui();

        void draw_line_separator();

        std::string CurrentTextDisplay;
        std::string LoadTextFile(const std::string& _filePath);

        std::unordered_map<MELT::Entity, bool> Entities;

        std::vector<std::string> Components;

        const char* PROJECT_SETTING_PATH = "../Project/ProjectSettings.yaml";
        const char* SCENE_PATH           = "../Project/Assets/Scenes/Scene.yaml";

        void SaveScene();
        void TestSave();

        const ImU32 BackgroundColor;

        void DrawSprite(const MELT::TextureData_old& _textureData, ImVec2 _position, ImVec2 _spriteSize, ImVec2 _spritePosition);
        void DrawSpriteWithDrawList(ImTextureID texture_id, ImVec2 position, ImVec2 sprite_size, ImVec2 sprite_position);

    private:
    };
}

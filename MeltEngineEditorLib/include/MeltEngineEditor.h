#pragma once
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <functional>
#include <filesystem>
#include <unordered_map>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "ImGuizmo.h"

//not good
#include "glm/gtc/type_ptr.hpp"

#include "IconsKenney.h"

#include "MeltEngine.h"

#include "SpriteEditorGUI.h"
#include "ScriptEditorGUI.h"
#include "ConsoleGUI.h"

#include "nfd.h"

namespace MELT_EDITOR
{
    class Editor
    {   
    public:
        MELT::Engine* Engine;

        std::vector<std::string> fileNames;

        std::filesystem::path CurrentWorkingProjectRootPath;

        SpriteEditorGUI SpriteEditorGUI;
        ScriptEditorGUI ScriptEditorGUI;
        ConsoleGUI ConsoleGUI;

        bool SpriteEditorDisplayed;

        explicit Editor(MELT::Engine* _engine);
        ~Editor();

        void UpdateInput(SDL_Event _event);
        void Update();

        void GetContent();

        void DrawMainMenubar();
        void DrawSceneViewGUI();
        void DrawHierarchyGUI();
        void DrawInspectorGUI();
        void DrawAssetsGUI();
        void DrawContentGUI();

        void DrawTransformComponentPanel(MELT::Transform& _transform);
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

        void DrawSprite(const MELT::TextureData& _textureData, ImVec2 _position, ImVec2 _spriteSize, ImVec2 _spritePosition);
        void DrawSpriteWithDrawList(ImTextureID texture_id, ImVec2 position, ImVec2 sprite_size, ImVec2 sprite_position);
    };
}

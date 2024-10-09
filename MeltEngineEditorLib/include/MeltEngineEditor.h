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
#include "MeltEngine.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "IconsKenney.h"
#include "ScriptEditorGUI.h"

namespace MELT_EDITOR
{
    class Editor
    {   
    public:
        MELT::Engine* Engine;

        std::vector<std::string> fileNames;

        ScriptEditorGUI ScriptEditorGUI;

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

        void DrawComponentPanel(std::size_t _id);

        std::string CurrentTextDisplay;
        std::string LoadTextFile(const std::string& _filePath);


        std::unordered_map<MELT::Entity, bool> Entities;

        std::vector<std::string> Components;

        const char* PROJECT_SETTING_PATH = "../Project/ProjectSettings.yaml";
        const char* SCENE_PATH           = "../Project/Scene.yaml";

        void SaveScene();
        void TestSave();

        const ImU32 BackgroundColor;
    };
}

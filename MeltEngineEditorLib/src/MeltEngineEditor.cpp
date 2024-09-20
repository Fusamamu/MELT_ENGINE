#include <iostream>
#include "MeltEngineEditor.h"

namespace MELT_EDITOR
{
    Editor::Editor(MELT::Engine* _engine):
        Engine(_engine)
    {
        std::cout << "Editor ctor" << std::endl;
        IMGUI_CHECKVERSION();

        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui::StyleColorsDark();

        const char* glsl_version = "#version 150";

        ImGui_ImplSDL2_InitForOpenGL(_engine->GetWindow(), _engine->GetGLContext());
        ImGui_ImplOpenGL3_Init(glsl_version);

        Engine->UpdateEditorInput = std::bind(&Editor::UpdateInput, this, std::placeholders::_1);
        Engine->UpdateEditor      = std::bind(&Editor::Update     , this);

        try
        {
            for(const auto& _entry : std::filesystem::directory_iterator("../"))
                fileNames.push_back(_entry.path().filename());
        }
        catch(const std::filesystem::filesystem_error& _e)
        {
            std::cout << "ERROR : " << _e.what() << std::endl;
        }
    }

    Editor::~Editor()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    } 

    void Editor::UpdateInput(SDL_Event _event)
    {
        ImGui_ImplSDL2_ProcessEvent(&_event);
    }

    void Editor::Update()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // Create a global menu bar
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open", "Ctrl+O"))
                {
                    // Handle "Open" action
                }
                if (ImGui::MenuItem("Save", "Ctrl+S"))
                {
                    // Handle "Save" action
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo", "Ctrl+Z"))
                {
                    // Handle "Undo" action
                }
                if (ImGui::MenuItem("Redo", "Ctrl+Y"))
                {
                    // Handle "Redo" action
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Help"))
            {
                if (ImGui::MenuItem("About"))
                {
                    // Handle "About" action
                }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }

        ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());



        if (ImGui::Begin("Content"))
        {
            static int _selected = -1;
            for(std::size_t _i = 0; _i < fileNames.size(); ++_i)
            {
                if(ImGui::Selectable(fileNames[_i].c_str(), _selected == _i))
                {
                    _selected = _i;
                    CurrentTextDisplay = LoadTextFile("../" +  fileNames[_i]);
                }
            }
        }
        ImGui::End();

        if (ImGui::Begin("Inspector"))
        {
            if(!CurrentTextDisplay.empty())
                ImGui::TextUnformatted(CurrentTextDisplay.c_str());
        }
        ImGui::End();

        if (ImGui::Begin("Hierarchy"))
        {
            if (ImGui::BeginPopupContextWindow()) {
                if (ImGui::MenuItem("Create object")) {
                    // Handle Property 1 action
                }
                ImGui::EndPopup();
            }
        }
        ImGui::End();


        ImGui::ShowDemoWindow(); // Show demo window! :)

        if (ImGui::Begin("SCENE VIEW"))
        {
            const float window_width  = ImGui::GetContentRegionAvail().x;
            const float window_height = ImGui::GetContentRegionAvail().y;

            Engine->ScreenWidth  = window_width;
            Engine->ScreenHeight = window_height;

            ImVec2 pos = ImGui::GetCursorScreenPos();

            ImGui::GetWindowDrawList()->AddImage(
                    (void*)Engine->m_Quad->TextureID,
                    ImVec2(pos.x, pos.y),
                    ImVec2(pos.x + window_width, pos.y + window_height),
                    ImVec2(0, 1),
                    ImVec2(1, 0)
            );
        }
        ImGui::End();
        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }
    }

    void Editor::GetContent()
    {

    }

    std::string Editor::LoadTextFile(const std::string &_filePath)
    {
        std::ifstream _inputFile (_filePath);
        if(!_inputFile.is_open())
        {
            std::cerr << "Could not open file path : " << _filePath << std::endl;
            return "";
        }
        std::stringstream _buffer;
        _buffer << _inputFile.rdbuf();
        return _buffer.str();
    }
}

#include <iostream>
#include "MeltEngineEditor.h"

namespace MELT_EDITOR
{
    unsigned int WindowBackground_Color = IM_COL32(33, 36, 35, 255);
    unsigned int ChildBackground_Color  = IM_COL32(26, 28, 27, 255);

    Editor::Editor():
        engine(nullptr),
        BackgroundColor(IM_COL32(8, 14, 15, 255))
    {
    }

    Editor::~Editor() = default;

    void Editor::init()
    {
        engine = new MELT::Engine();
        engine->init();

        IMGUI_CHECKVERSION();

        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui::StyleColorsDark();

        io.Fonts->AddFontFromFileTTF("../MeltEngineEditorLib/res/fonts/JetBrainsMono-1.0.2/ttf/JetBrainsMono-Regular.ttf", 15.0f); // Example font size: 18
        static const ImWchar icons_ranges[] = { ICON_MIN_KI, ICON_MAX_KI, 0 };
        ImFontConfig icons_config;
        icons_config.MergeMode = true;
        io.Fonts->AddFontFromFileTTF("../MeltEngineEditorLib/res/icons/kenney/kenney-icon-font.ttf", 16.0f, &icons_config, icons_ranges);

        ImGuiStyle& _style = ImGui::GetStyle();

        _style.Colors[ImGuiCol_WindowBg]             = ImVec4(8.0f / 255.0f, 14.0f / 255.0f, 15.0f / 255.0f, 1.0f);
        _style.Colors[ImGuiCol_TitleBg]              = ImColor(33, 36, 35);
        _style.Colors[ImGuiCol_TitleBgActive]        = ImColor(33, 36, 35);
        _style.Colors[ImGuiCol_Border]               = ImVec4(33.0f / 255.0f, 36.0f / 255.0f, 35.0f / 255.0f, 1.0f);
        _style.Colors[ImGuiCol_BorderShadow]         = ImVec4(33.0f / 255.0f, 36.0f / 255.0f, 35.0f / 255.0f, 1.0f);
        _style.Colors[ImGuiCol_Header]               = ImVec4(33.0f / 255.0f, 36.0f / 255.0f, 35.0f / 255.0f, 1.0f);
        _style.Colors[ImGuiCol_HeaderHovered]        = ImVec4(172.0f / 255.0f, 184.0f / 255.0f, 39.0f / 255.0f, 1.0f);
        _style.Colors[ImGuiCol_HeaderActive]         = ImVec4(172.0f / 255.0f, 184.0f / 255.0f, 39.0f / 255.0f, 1.0f);
        _style.Colors[ImGuiCol_Separator]            = ImVec4(33.0f / 255.0f, 36.0f / 255.0f, 35.0f / 255.0f, 1.0f);
        _style.Colors[ImGuiCol_FrameBgActive]        = ImVec4(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f);
        _style.Colors[ImGuiCol_Tab]                  = ImVec4(59.0f / 255.0f, 53.0f / 255.0f, 51.0f / 255.0f, 1.0f);
        _style.Colors[ImGuiCol_TabActive]            = ImVec4(230.0f / 255.0f, 150.0f / 255.0f, 30.0f / 255.0f, 1.0f);
        _style.Colors[ImGuiCol_TabUnfocusedActive]   = ImVec4(59.0f / 255.0f, 53.0f / 255.0f, 51.0f / 255.0f, 1.0f);
        _style.Colors[ImGuiCol_TabUnfocused]         = ImVec4(59.0f / 255.0f, 53.0f / 255.0f, 51.0f / 255.0f, 1.0f);
        _style.Colors[ImGuiCol_TabHovered]           = ImVec4(232.0f / 255.0f, 194.0f / 255.0f, 58.0f / 255.0f, 1.0f);
        _style.Colors[ImGuiCol_TabSelectedOverline]  = ImVec4(59.0f / 255.0f, 53.0f / 255.0f, 51.0f / 255.0f, 0.0f);

        const char* glsl_version = "#version 150";

        ImGui_ImplSDL2_InitForOpenGL(engine->sdl_window, engine->gl_context);
        ImGui_ImplOpenGL3_Init(glsl_version);

        try
        {
            for(const auto& _entry : std::filesystem::directory_iterator("../"))
                fileNames.push_back(_entry.path().filename());
        }
        catch(const std::filesystem::filesystem_error& _e)
        {
            std::cout << "ERROR : " << _e.what() << std::endl;
        }

        console_gui     .EditorOwner = this;
        sprite_editor_gui.EditorOwner = this;
        sprite_editor_gui.Init();
        scene_view_gui  .init(this);
        project_gui     .init(this);
        hierarchy_gui   .init(this);
        node_graph_gui  .init(this);
        inspector_gui   .init(this);
        system_gui      .init(this);
        ui_system_gui   .init(this);

        NFD_Init();

        application_mode_manager.add_state<EditorMode>    (this);
        application_mode_manager.add_state<TileEditorMode>(this);
        application_mode_manager.add_state<GameplayMode>  (this);
        application_mode_manager.set_initial_state<EditorMode>();
    }

    void Editor::update()
    {
        application_mode_manager.update(0.0f);
    }

    void Editor::update_input(SDL_Event _event)
    {
        ImGui_ImplSDL2_ProcessEvent(&_event);
    }

    void Editor::update_gui()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        ImGuizmo::BeginFrame();

        draw_main_menubar();
        ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());

        //draw_scene_view_gui    ();

        bool _is_edit_mode = application_mode_manager.is_current_mode<EditorMode>();
        if (!_is_edit_mode)
            ImGui::BeginDisabled();

        draw_gameplay_view_gui ();
        draw_material_gui      ();
        draw_content_gui       ();
        draw_render_pipeline_gui();

        if (!_is_edit_mode)
            ImGui::EndDisabled();

        scene_view_gui   .draw_gui();
        sprite_editor_gui.draw_gui();
        script_editor_gui.draw_gui();
        console_gui      .draw_gui();
        project_gui      .draw_gui();
        hierarchy_gui    .draw_gui();
        node_graph_gui   .draw_gui();
        inspector_gui    .draw_gui();
        system_gui       .draw_gui();
        ui_system_gui    .draw_gui();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }
    }

    void Editor::quit()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
        NFD_Quit();

        engine->quit();
        delete engine;
    }

    void Editor::GetContent()
    {

    }

    bool CompileScript(const std::string& scriptPath, std::string& output) {
        std::string command = "g++ -dynamiclib -o libscript.dylib " + scriptPath + " 2>&1"; // Redirect stderr to stdout
        FILE* pipe = popen(command.c_str(), "r"); // Open a pipe to capture output
        if (!pipe)
            return false;

        char buffer[128];
        output.clear();
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            output += buffer;
        }
        return pclose(pipe) == 0;
    }

    typedef void (*HelloFunc)();

    void Editor::draw_main_menubar()
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Test compile"))
                {
                    int result = std::system("cmake --build ../Project/build");

                    if (result != 0)
                    {
                        std::cerr << "CMake build failed!\n";
                        return;
                    }

                    void* _handle = dlopen("../Project/build/libCustomNativeScript.dylib", RTLD_LAZY);
                    if (!_handle)
                    {
                        std::cerr << "Failed to load dylib: " << dlerror() << std::endl;
                        return;
                    }

                    dlerror();

                    HelloFunc _hello = (HelloFunc)dlsym(_handle, "hello_from_dylib");

                    if (const char* error = dlerror())
                    {
                        std::cerr << "Failed to load symbol: " << error << std::endl;
                        dlclose(_handle);
                        return;
                    }

                    _hello();

                    dlclose(_handle);
                }

                if (ImGui::MenuItem("New project"))
                {
                    nfdu8char_t *outPath;
                    nfdpickfolderu8args_t _args { 0 };
                    nfdresult_t result = NFD_PickFolderU8_With(&outPath, &_args);

                    if (result == NFD_OKAY)
                    {
                        puts("Success!");
                        puts(outPath);
                        NFD_FreePathU8(outPath);
                    }
                    else if (result == NFD_CANCEL)
                    {
                        puts("User pressed cancel.");
                    }
                    else
                    {
                        printf("Error: %s\n", NFD_GetError());
                    }
                }

                if (ImGui::MenuItem("Open", "Ctrl+O"))
                {
                    nfdu8char_t *outPath;
                    nfdpickfolderu8args_t _args { 0 };
                    nfdresult_t result = NFD_PickFolderU8_With(&outPath, &_args);

                    if (result == NFD_OKAY)
                    {
                        puts("Success!");
                        puts(outPath);
                        working_project_directory = outPath;
                        NFD_FreePathU8(outPath);
                    }
                    else if (result == NFD_CANCEL)
                    {
                        puts("User pressed cancel.");
                    }
                    else
                    {
                        printf("Error: %s\n", NFD_GetError());
                    }
                }
                if (ImGui::MenuItem("Save", "Ctrl+S"))
                    TestSave();
                if (ImGui::MenuItem("Save scene"))
                    SaveScene();
                if (ImGui::MenuItem("Load scene"))
                {
                    nfdu8char_t* outPath = nullptr;
                    nfdu8filteritem_t filterItem[1] =
                    {
                        { "YAML Scene", "yaml" }
                    };

                    nfdopendialogu8args_t args = { 0 };
                    args.filterCount = 1;
                    args.filterList = filterItem;

                    nfdresult_t result = NFD_OpenDialogU8_With(&outPath, &args);

                    if (result == NFD_OKAY)
                    {
                        std::filesystem::path sceneFilePath(outPath);
                        std::ifstream sceneFile(sceneFilePath);

                        if (!sceneFile.is_open())
                        {
                            std::cerr << "Failed to open scene file: " << sceneFilePath << std::endl;
                        }
                        else
                        {
                            std::stringstream buffer;
                            buffer << sceneFile.rdbuf();
                            sceneFile.close();

                            std::string yamlString = buffer.str();

                            MELT::YAMLSceneSerializer _serializer;

                            _serializer.deserialize_scene(*engine->manager_registry.get<MELT::SceneManager>()->working_scene, yamlString);

                            engine->Logger.log("Scene loaded from: " + sceneFilePath.string());
                        }
                        NFD_FreePathU8(outPath);
                    }
                    else if (result == NFD_CANCEL)
                    {
                        puts("User pressed cancel.");
                    }
                    else
                    {
                        printf("Error: %s\n", NFD_GetError());
                    }
                }


                if (ImGui::MenuItem("Create material"))
                {
                    std::string _target_path = "../Project/Assets/default_material.mat";

                    std::string _save_text = MELT::GRAPHIC::create_material();

                    if (!std::filesystem::exists(_target_path))
                    {
                        std::ofstream _f_out(_target_path);
                        _f_out << _save_text.c_str();
                        _f_out.close();

                        engine->Logger.log("Created new YAML file");
                    } else {

                        std::ofstream _file;
                        _file.open(_target_path);
                        _file << _save_text.c_str();
                        _file.close();

                        engine->Logger.log("File already exists");
                    }
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo", "Ctrl+Z"))
                {
                }
                if (ImGui::MenuItem("Redo", "Ctrl+Y"))
                {
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Window"))
            {
                if (ImGui::MenuItem("Sprite Editor"))
                    sprite_editor_gui.Open();
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

        ImGuiViewport* viewport = ImGui::GetMainViewport();

        ImGui::SetNextWindowPos (ImVec2(-1.0f, ImGui::GetFrameHeight()));
        ImGui::SetNextWindowSize(ImVec2(viewport->Size.x + 2.0f, ImGui::GetFrameHeight()));

        ImGuiWindowFlags flags =
                ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs |
                ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse |
                ImGuiWindowFlags_NoSavedSettings |
                ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoBackground |
                ImGuiWindowFlags_MenuBar;

        if (ImGui::Begin("StatusBar", nullptr, flags))
        {
            if (ImGui::BeginMenuBar())
            {
                ImGui::Text("Test second menubar");
                ImGui::Text("Test second menubar");
                ImGui::Text("Test second menubar");
                ImGui::EndMenuBar();
            }
            ImGui::End();
        }
        viewport->WorkPos.y += ImGui::GetFrameHeight();
        viewport->WorkSize.y -= ImGui::GetFrameHeight();
    }

    void Editor::draw_gameplay_view_gui()
    {
        MELT::Scene* _working_scene = engine->manager_registry.get<MELT::SceneManager>()->working_scene;

        if (ImGui::Begin("Game"))
        {
            ImVec2 _cursorScreenPos = ImGui::GetCursorScreenPos();

            const float _scene_editor_window_width  = ImGui::GetContentRegionAvail().x;
            const float _scene_editor_window_height = ImGui::GetContentRegionAvail().y;

            ImGuizmo::SetOrthographic(true);
            ImGuizmo::SetDrawlist();
            ImGuizmo::SetRect(_cursorScreenPos.x, _cursorScreenPos.y, _scene_editor_window_width, _scene_editor_window_height);

            ImGui::GetWindowDrawList()->AddImage(
                    (void*)(intptr_t)engine->manager_registry.get<MELT::RenderPipeline>()->editor_scene_frame_buffer.texture_id,
                    ImVec2(_cursorScreenPos.x, _cursorScreenPos.y),
                    ImVec2(_cursorScreenPos.x + _scene_editor_window_width, _cursorScreenPos.y + _scene_editor_window_height),
                    ImVec2(0, 1),
                    ImVec2(1, 0)
            );

            engine->main_camera.WindowSize.x = _scene_editor_window_width;
            engine->main_camera.WindowSize.y = _scene_editor_window_height;
            engine->main_camera.update_screen_size_with_orthographic_size(_scene_editor_window_width / _scene_editor_window_height);
        }
        ImGui::End();
    }

    void Editor::draw_material_gui()
    {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ChildBackground_Color);
        if (ImGui::Begin("Material Inspector"))
        {
            ImGui::Text("Mesh");
            ImGui::SameLine(120.0f);
            ImGui::Text("name :");
            ImGui::Text("");
            ImGui::SameLine(120.0f);
            ImGui::Text("uuid : ");

            std::shared_ptr<MELT::RenderPipeline> _render_pipeline = engine->manager_registry.get<MELT::RenderPipeline>();

            if (ImGui::ColorEdit4("##picker", &_render_pipeline->shader_preview.clear_color[0], ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel)) {
                // color changed!
            }

            float availableHeight = ImGui::GetContentRegionAvail().y;
            float windowWidth     = ImGui::GetContentRegionAvail().x;

            ImGui::Dummy(ImVec2(0, availableHeight - windowWidth)); // Push everything down

            ImVec2 imageSize(windowWidth, windowWidth); // Square: width == height
            //ImGui::Image((void*)(intptr_t)Engine->manager_registry.get<MELT::RenderPipeline>()->editor_scene_frame_buffer->texture_id, imageSize);

            ImGui::Image(engine->manager_registry.get<MELT::RenderPipeline>()->shader_preview_texture(), imageSize);
        }
        ImGui::End();
        ImGui::PopStyleColor();
    }

    void Editor::draw_content_gui()
    {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ChildBackground_Color);
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
        ImGui::PopStyleColor();
    }

    void Editor::draw_render_pipeline_gui()
    {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ChildBackground_Color);
        if (ImGui::Begin("Render Pipeline"))
        {
            std::shared_ptr<MELT::RenderPipeline> _render_pipeline = engine->manager_registry.get<MELT::RenderPipeline>();

            ImGui::ColorEdit4("Color with Alpha", &_render_pipeline->clear_color[0]);
        }
        ImGui::End();
        ImGui::PopStyleColor();
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

    void Editor::TestSave()
    {
        YAML::Node _root;

        _root["Test"] = "Test";
        std::ofstream _file;
        _file.open(PROJECT_SETTING_PATH);
        _file << _root;
        _file.close();
    }

    void Editor::SaveScene()
    {
        MELT::YAMLSceneSerializer _serializer;

        std::string _save_text = _serializer.serialize_scene(*engine->manager_registry.get<MELT::SceneManager>()->working_scene);

        if (!std::filesystem::exists(SCENE_PATH))
        {
            std::ofstream _f_out(SCENE_PATH);
            _f_out << _save_text.c_str();
            _f_out.close();

            engine->Logger.log("Created new YAML file");
        } else {

            std::ofstream _file;
            _file.open(SCENE_PATH);
            _file << _save_text.c_str();
            _file.close();

            engine->Logger.log("File already exists");
        }
    }

    void Editor::DrawSprite(const MELT::TextureData_old& _textureData, ImVec2 _position, ImVec2 _spriteSize, ImVec2 _spritePosition)
    {
        float texture_width  = static_cast<float>(_textureData.Width);
        float texture_height = static_cast<float>(_textureData.Height);

        ImVec2 uv0 = ImVec2(_spritePosition.x / texture_width, _spritePosition.y / texture_height);

        ImVec2 uv1 = ImVec2((_spritePosition.x + _spriteSize.x) / texture_width,
                            (_spritePosition.y + _spriteSize.y) / texture_height);

        ImTextureID textureID = (void*)(intptr_t)_textureData.TextureID;

        ImGui::GetWindowDrawList()->AddImage(textureID,
                                             _position,
                                             ImVec2(_position.x + _spriteSize.x, _position.y + _spriteSize.y),
                                             uv0, uv1);
    }

    void Editor::draw_line_separator()
    {
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        // Get full window boundaries
        ImVec2 window_pos  = ImGui::GetWindowPos();
        ImVec2 window_size = ImGui::GetWindowSize();

        float line_y = ImGui::GetCursorScreenPos().y;
        // Draw the full-width line
        draw_list->AddLine(
            ImVec2(window_pos.x, line_y),
            ImVec2(window_pos.x + window_size.x, line_y),
            IM_COL32(50, 50, 50, 255), // white
            1.5f // thickness
        );
        ImGui::Dummy(ImVec2(0.0f, 5.0f)); // Optional: move cursor down after line so next element doesn't overlap
    }
}

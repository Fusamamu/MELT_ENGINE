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

        NFD_Init();

        application_mode_manager.add_state<EditorMode>  (this);
        application_mode_manager.add_state<GameplayMode>(this);
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

    // ImVec2 RemapImVec2(const ImVec2& value,
    //                    float originalMinX, float originalMaxX,
    //                    float targetMinX, float targetMaxX,
    //                    float originalMinY, float originalMaxY,
    //                    float targetMinY, float targetMaxY)
    // {
    //     ImVec2 result;
    //     // Remap X component
    //     result.x = targetMinX + ((value.x - originalMinX) / (originalMaxX - originalMinX)) * (targetMaxX - targetMinX);
    //     // Remap Y component
    //     result.y = targetMinY + ((value.y - originalMinY) / (originalMaxY - originalMinY)) * (targetMaxY - targetMinY);
    //     return result;
    // }

    void Editor::draw_scene_view_gui()
    {
        // MELT::Scene* _working_scene = engine->manager_registry.get<MELT::SceneManager>()->working_scene;
        //
        // if (ImGui::Begin("Scene view"))
        // {
        //     ImVec2 _cursor_screen_pos = ImGui::GetCursorScreenPos();
        //     const float _scene_editor_window_width  = ImGui::GetContentRegionAvail().x;
        //     const float _scene_editor_window_height = ImGui::GetContentRegionAvail().y;
        //
        //     ImGuizmo::SetOrthographic(true); // or true if using orthographic
        //     ImGuizmo::SetDrawlist();
        //     ImGuizmo::SetRect(_cursor_screen_pos.x, _cursor_screen_pos.y, _scene_editor_window_width, _scene_editor_window_height);
        //
        //     if (ImGui::IsWindowHovered())
        //     {
        //         if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        //         {
        //             if (!ImGuizmo::IsOver() && !ImGuizmo::IsUsing() || !_working_scene->selected_node_id.has_value())
        //             {
        //                 engine->deselect_all_nodes();
        //                 engine->select_object(MELT::Input.MouseScreenPosition, engine->MainCamera);
        //             }
        //         }
        //     }
        //
        //     ImGui::GetWindowDrawList()->AddImage(
        //             (void*)(intptr_t)engine->manager_registry.get<MELT::RenderPipeline>()->editor_scene_frame_buffer->texture_id,
        //             ImVec2(_cursor_screen_pos.x, _cursor_screen_pos.y),
        //             ImVec2(_cursor_screen_pos.x + _scene_editor_window_width, _cursor_screen_pos.y + _scene_editor_window_height),
        //             ImVec2(0, 1),
        //             ImVec2(1, 0)
        //     );
        //
        //     static ImGuizmo::OPERATION currentOperation = ImGuizmo::TRANSLATE;
        //
        //     if (ImGui::Button("Translate"))
        //         currentOperation = ImGuizmo::TRANSLATE;
        //     ImGui::SameLine();
        //     if (ImGui::Button("Rotate"))
        //         currentOperation = ImGuizmo::ROTATE;
        //     ImGui::SameLine();
        //     if (ImGui::Button("Scale"))
        //         currentOperation = ImGuizmo::SCALE;
        //
        //     if (_working_scene->selected_node_id.has_value())
        //     {
        //         MELT::Node* _node = _working_scene->get_selected_node();
        //
        //         auto& transform = _node->get_component<MELT::Transform>();
        //
        //         glm::mat4 _object_matrix = transform.get_transform_matrix();
        //
        //         ImGuizmo::Manipulate(
        //             glm::value_ptr(engine->MainCamera.get_view_matrix()),
        //             glm::value_ptr(engine->MainCamera.get_orthographic_projection_matrix()),
        //             currentOperation,
        //             ImGuizmo::WORLD,
        //             glm::value_ptr(_object_matrix)
        //         );
        //
        //         if (ImGuizmo::IsUsing())
        //         {
        //             ImGuizmo::DecomposeMatrixToComponents(
        //                 glm::value_ptr(_object_matrix),
        //                 glm::value_ptr(transform.position),
        //                 glm::value_ptr(transform.rotation),
        //                 glm::value_ptr(transform.scale));
        //         }
        //     }
        //
        //     engine->MainCamera.WindowSize.x = _scene_editor_window_width;
        //     engine->MainCamera.WindowSize.y = _scene_editor_window_height;
        //     engine->MainCamera.UpdateScreenSizeWithOrthographicSize(_scene_editor_window_width / _scene_editor_window_height);
        //
        //     MELT::Input.MouseWindowPosition.x = ImGui::GetMousePos().x;
        //     MELT::Input.MouseWindowPosition.y = ImGui::GetMousePos().y;
        //     MELT::Input.MouseScreenPosition.x = ImVec2(MELT::Input.MouseWindowPosition.x - _cursor_screen_pos.x, MELT::Input.MouseWindowPosition.y - _cursor_screen_pos.y).x;
        //     MELT::Input.MouseScreenPosition.y = ImVec2(MELT::Input.MouseWindowPosition.x - _cursor_screen_pos.x, MELT::Input.MouseWindowPosition.y - _cursor_screen_pos.y).y;
        //
        //
        //     ImVec2 _screenPos     = ImVec2(MELT::Input.MouseWindowPosition.x - _cursor_screen_pos.x, MELT::Input.MouseWindowPosition.y - _cursor_screen_pos.y);
        //     ImVec2 _normalizedPos = RemapImVec2(_screenPos,
        //                                         0.0f, _scene_editor_window_width , 0.0f, 1.0f,
        //                                         0.0f, _scene_editor_window_height, 0.0f, 1.0f);
        //
        //     ImVec2 _mouseWorldPos = RemapImVec2(_screenPos,
        //                                         0.0f, _scene_editor_window_width , -engine->MainCamera.HalfScreenWidth(),  engine->MainCamera.HalfScreenWidth(),
        //                                         0.0f, _scene_editor_window_height,  engine->MainCamera.HalfScreenHeight(), -engine->MainCamera.HalfScreenHeight());
        //
        //     _mouseWorldPos.x += engine->MainCamera.Position.x;
        //     _mouseWorldPos.y += engine->MainCamera.Position.y;
        //
        //
        //     MELT::Input.MouseScreenNormalizedPosition.x = _normalizedPos.x;
        //     MELT::Input.MouseScreenNormalizedPosition.y = _normalizedPos.y;
        //     MELT::Input.MouseScreenWorldPosition.x      = _mouseWorldPos.x;
        //     MELT::Input.MouseScreenWorldPosition.y      = _mouseWorldPos.y;
        //
        //     ImGui::Text("Window content          W H : (%.1f, %.1f)"     , _scene_editor_window_width                 , _scene_editor_window_height                );
        //     ImGui::Text("Orthographic projection W H : (%.1f, %.1f)"     , engine->MainCamera.ScreenSize.x            , engine->MainCamera.ScreenSize.y            );
        //     ImGui::Text("Mouse window position       : (%.1f, %.1f)"     , MELT::Input.MouseWindowPosition .x         , MELT::Input.MouseWindowPosition .y         );
        //     ImGui::Text("Mouse screen position       : (%.1f, %.1f)"     , MELT::Input.MouseScreenPosition.x          , MELT::Input.MouseScreenPosition.y          );
        //     ImGui::Text("Normalized position         : (%.1f, %.1f)"     , MELT::Input.MouseScreenNormalizedPosition.x, MELT::Input.MouseScreenNormalizedPosition.y);
        //     ImGui::Text("Mouse world position        : (%.1f, %.1f)"     , MELT::Input.MouseScreenWorldPosition.x     , MELT::Input.MouseScreenWorldPosition.y     );
        //     ImGui::InputFloat3("Camera position", glm::value_ptr(engine->MainCamera.Position));
        //     ImGui::SliderFloat("Near plane"       , &engine->MainCamera.near_plane, -100.0f, 0.0f);
        //     ImGui::SliderFloat("Far plane"        , &engine->MainCamera.far_plane ,     0.0, 1000.0f);
        //     ImGui::SliderFloat("Orthographic size", &engine->MainCamera.OrthographicSize, 1.0f, 200.f);
        //
        //
        //     auto _ent_view = _working_scene->ecs_registry.view<MELT::Transform, MELT::Light>();
        //
        //     for (auto _entity : _ent_view)
        //     {
        //         auto& _transform = _ent_view.get<MELT::Transform>(_entity);
        //
        //         M_VEC3 _world_pos = _transform.position;
        //
        //         glm::mat4 _view           = engine->MainCamera.get_view_matrix();
        //         glm::mat4 _projection     = engine->MainCamera.get_orthographic_projection_matrix();
        //         glm::vec4 _clip_space_pos = _projection * _view * glm::vec4(_world_pos, 1.0f);
        //
        //         glm::vec2 ndc = glm::vec2(_clip_space_pos.x, _clip_space_pos.y);
        //         glm::vec2 screenNormalized = ndc * 0.5f + 0.5f;
        //
        //         glm::vec2 screenPos = glm::vec2(
        //                     screenNormalized.x  * _scene_editor_window_width  + _cursor_screen_pos.x,
        //             (1.0f - screenNormalized.y) * _scene_editor_window_height + _cursor_screen_pos.y); // flip Y
        //
        //         ImVec2 winPos = ImGui::GetWindowPos();
        //         ImVec2 winSize = ImGui::GetWindowSize();
        //         ImVec2 winMin = winPos;
        //         ImVec2 winMax = ImVec2(winPos.x + winSize.x, winPos.y + winSize.y);
        //
        //         //Only draw if inside the window region
        //         if (screenPos.x >= winMin.x && screenPos.x <= winMax.x &&
        //             screenPos.y >= winMin.y && screenPos.y <= winMax.y)
        //         {
        //             ImVec2 boxSize = ImVec2(80.0f, 20.0f); // width x height
        //             ImVec2 rectMin = ImVec2(screenPos.x - boxSize.x * 0.5f, screenPos.y - boxSize.y - 5.0f);
        //             ImVec2 rectMax = ImVec2(screenPos.x + boxSize.x * 0.5f, screenPos.y - 5.0f);
        //
        //             // ImDrawList* drawList = ImGui::GetWindowDrawList();
        //             // drawList->AddRectFilled(rectMin, rectMax, IM_COL32( 30, 144, 255, 220), 6.0f); // background
        //             // drawList->AddRect      (rectMin, rectMax, IM_COL32(255, 255, 255, 255), 6.0f);      // border
        //
        //             ImVec2 textSize = ImGui::CalcTextSize("Label!");
        //             ImVec2 textPos = ImVec2(
        //                 rectMin.x + (rectMax.x - rectMin.x - textSize.x) * 0.5f,
        //                 rectMin.y + (rectMax.y - rectMin.y - textSize.y) * 0.5f
        //             );
        //
        //             //drawList->AddText(textPos, IM_COL32(255, 255, 255, 255), "Camera");
        //
        //             MELT::TextureData* _camera_icon = engine->manager_registry.get<MELT::ResourceManager>()->get_texture_data("camera_icon.png");
        //             ImTextureID _camera_icon_id = (ImTextureID)(intptr_t)_camera_icon->p_texture->texture_id;
        //
        //             MELT::TextureData* _light_icon = engine->manager_registry.get<MELT::ResourceManager>()->get_texture_data("light_icon.png");
        //             ImTextureID _light_icon_id = (ImTextureID)(intptr_t)_light_icon->p_texture->texture_id;
        //
        //             const ImVec2 size = ImVec2(32, 32);
        //             ImVec2 drawMin = ImVec2(screenPos.x - size.x * 0.5f, screenPos.y - size.y);
        //             ImVec2 drawMax = ImVec2(drawMin.x + size.x         , drawMin.y   + size.y);
        //
        //             // Step 5: Draw the texture
        //             ImGui::GetWindowDrawList()->AddImage(_light_icon_id, drawMin, drawMax);
        //         }
        //     }
        //
        //     // Push to bottom
        //     float padding = 10.0f; // Space from bottom edge
        //     float button_width = 120.0f;
        //     float button_height = 0.0f; // 0 = auto
        //
        //     ImVec2 window_size = ImGui::GetWindowSize();
        //     ImVec2 cursor_pos = ImGui::GetCursorScreenPos();
        //
        //     // Move to bottom center
        //     ImGui::SetCursorPosY(window_size.y - padding - ImGui::GetFrameHeight() * 4.0f); // Align bottom
        //     ImGui::SetCursorPosX((window_size.x - button_width) * 0.5f);             // Align center
        //
        //     static int selected = 0;
        //
        //     auto ToggleButton = [](const char* label, int index, int& selected, std::function<void()> onClick = nullptr, ImVec2 size = ImVec2(100, 30))
        //     {
        //         float roundness = 10.0f;
        //
        //         ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, roundness);
        //         if (selected == index)
        //             ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.6f, 1.0f, 1.0f));
        //         else
        //             ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyle().Colors[ImGuiCol_Button]);
        //
        //         if (ImGui::Button(label, size)) {
        //             selected = index;
        //             if (onClick)
        //                 onClick(); // Call the function!
        //         }
        //
        //         ImGui::PopStyleColor();
        //         ImGui::PopStyleVar();
        //     };
        //
        //     ToggleButton("PLAY", 0, selected, [&]() {
        //         application_mode_manager.change_state<GameplayMode>();
        //     });
        //     ImGui::SameLine();
        //     ToggleButton("PAUSE", 1, selected, [&]() {
        //         application_mode_manager.change_state<EditorMode>();
        //     });
        //     ImGui::SameLine();
        //     ToggleButton("FORWARD", 2, selected, []() {
        //         printf("Right selected!\n");
        //     });
        // }
        // ImGui::End();
    }

    void Editor::draw_gameplay_view_gui()
    {
        MELT::Scene* _working_scene = engine->manager_registry.get<MELT::SceneManager>()->working_scene;

        if (ImGui::Begin("Game"))
        {
            ImVec2 _cursorScreenPos = ImGui::GetCursorScreenPos();

            const float _sceneEditorWindowWidth  = ImGui::GetContentRegionAvail().x;
            const float _sceneEditorWindowHeight = ImGui::GetContentRegionAvail().y;

            ImGuizmo::SetOrthographic(true);
            ImGuizmo::SetDrawlist();
            ImGuizmo::SetRect(_cursorScreenPos.x, _cursorScreenPos.y, _sceneEditorWindowWidth, _sceneEditorWindowHeight);

            ImGui::GetWindowDrawList()->AddImage(
                    (void*)(intptr_t)engine->manager_registry.get<MELT::RenderPipeline>()->editor_scene_frame_buffer->texture_id,
                    ImVec2(_cursorScreenPos.x, _cursorScreenPos.y),
                    ImVec2(_cursorScreenPos.x + _sceneEditorWindowWidth, _cursorScreenPos.y + _sceneEditorWindowHeight),
                    ImVec2(0, 1),
                    ImVec2(1, 0)
            );

            engine->main_camera.WindowSize.x = _sceneEditorWindowWidth;
            engine->main_camera.WindowSize.y = _sceneEditorWindowHeight;
            engine->main_camera.UpdateScreenSizeWithOrthographicSize(_sceneEditorWindowWidth / _sceneEditorWindowHeight);
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

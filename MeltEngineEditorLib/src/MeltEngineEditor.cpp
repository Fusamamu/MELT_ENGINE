#include <iostream>
#include "MeltEngineEditor.h"
// #include "MeshRenderer.h"
// #include "Components/BoxCollider.h"

namespace MELT_EDITOR
{
    unsigned int WindowBackground_Color = IM_COL32(33, 36, 35, 255);
    unsigned int ChildBackground_Color  = IM_COL32(26, 28, 27, 255);

    Editor::Editor(MELT::Engine* _engine):
        Engine(_engine),
        BackgroundColor(IM_COL32(8, 14, 15, 255))
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

        io.Fonts->AddFontFromFileTTF("../MeltEngineEditorLib/res/fonts/JetBrainsMono-1.0.2/ttf/JetBrainsMono-Regular.ttf", 15.0f); // Example font size: 18
        static const ImWchar icons_ranges[] = { ICON_MIN_KI, ICON_MAX_KI, 0 };
        ImFontConfig icons_config;
        icons_config.MergeMode = true;
        io.Fonts->AddFontFromFileTTF("../MeltEngineEditorLib/res/icons/kenney/kenney-icon-font.ttf", 16.0f, &icons_config, icons_ranges);

        ImGuiStyle& _style = ImGui::GetStyle();

        _style.Colors[ImGuiCol_WindowBg]             = ImVec4(8.0f / 255.0f, 14.0f / 255.0f, 15.0f / 255.0f, 1.0f);

        //_style.Colors[ImGuiCol_TitleBg]              = ImVec4(33.0f / 255.0f, 36.0f / 255.0f, 35.0f / 255.0f, 1.0f);

        _style.Colors[ImGuiCol_TitleBg]              = ImColor(33, 36, 35);
        //_style.Colors[ImGuiCol_TitleBg]              = ImColor(28, 31, 30);
        //_style.Colors[ImGuiCol_TitleBgActive]        = ImVec4(61.0f / 255.0f, 53.0f / 255.0f, 40.0f / 255.0f, 1.0f);
        _style.Colors[ImGuiCol_TitleBgActive]        = ImColor(33, 36, 35);


        _style.Colors[ImGuiCol_Border]               = ImVec4(33.0f / 255.0f, 36.0f / 255.0f, 35.0f / 255.0f, 1.0f);
        _style.Colors[ImGuiCol_BorderShadow]         = ImVec4(33.0f / 255.0f, 36.0f / 255.0f, 35.0f / 255.0f, 1.0f);

        _style.Colors[ImGuiCol_Header]               = ImVec4(33.0f / 255.0f, 36.0f / 255.0f, 35.0f / 255.0f, 1.0f);
        _style.Colors[ImGuiCol_HeaderHovered]        = ImVec4(172.0f / 255.0f, 184.0f / 255.0f, 39.0f / 255.0f, 1.0f);
        _style.Colors[ImGuiCol_HeaderActive]         = ImVec4(172.0f / 255.0f, 184.0f / 255.0f, 39.0f / 255.0f, 1.0f);

        //_style.Colors[ImGuiCol_HeaderActive]         = ImColor(33, 36, 35);

        _style.Colors[ImGuiCol_Separator]            = ImVec4(33.0f / 255.0f, 36.0f / 255.0f, 35.0f / 255.0f, 1.0f);
        _style.Colors[ImGuiCol_FrameBgActive]        = ImVec4(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f);
        _style.Colors[ImGuiCol_Tab]                  = ImVec4(59.0f / 255.0f, 53.0f / 255.0f, 51.0f / 255.0f, 1.0f);
        _style.Colors[ImGuiCol_TabActive]            = ImVec4(230.0f / 255.0f, 150.0f / 255.0f, 30.0f / 255.0f, 1.0f);
        _style.Colors[ImGuiCol_TabUnfocusedActive]   = ImVec4(59.0f / 255.0f, 53.0f / 255.0f, 51.0f / 255.0f, 1.0f);
        _style.Colors[ImGuiCol_TabUnfocused]         = ImVec4(59.0f / 255.0f, 53.0f / 255.0f, 51.0f / 255.0f, 1.0f);
        _style.Colors[ImGuiCol_TabHovered]           = ImVec4(232.0f / 255.0f, 194.0f / 255.0f, 58.0f / 255.0f, 1.0f);
        _style.Colors[ImGuiCol_TabSelectedOverline]  = ImVec4(59.0f / 255.0f, 53.0f / 255.0f, 51.0f / 255.0f, 0.0f);

        const char* glsl_version = "#version 150";

        ImGui_ImplSDL2_InitForOpenGL(_engine->sdl_window, _engine->gl_context);
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

        ConsoleGUI     .EditorOwner = this;
        SpriteEditorGUI.EditorOwner = this;
        SpriteEditorGUI.Init();

        NFD_Init();
    }

    Editor::~Editor()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
        NFD_Quit();
    }

    void Editor::UpdateInput(SDL_Event _event)
    {
        ImGui_ImplSDL2_ProcessEvent(&_event);
    }

    void DrawPanel()
    {
        ImDrawList* _drawList = ImGui::GetWindowDrawList();

        ImVec2 _panelPos = ImGui::GetCursorScreenPos();
        ImVec2 _panelSize (ImGui::GetWindowWidth() - 20.0f, 100.0f);

        _drawList->AddRectFilled(
                _panelPos,
                ImVec2(_panelPos.x + _panelSize.x, _panelPos.y + _panelSize.y),
                IM_COL32(28, 31, 29, 255), 6.0f);
    }

    void Editor::Update()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        ImGuizmo::BeginFrame();

        DrawMainMenubar();
        ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());

        DrawSceneViewGUI     ();
        DrawInspectorGUI     ();
        DrawMaterialGUI      ();
        DrawHierarchyGUI     ();
        DrawAssetsGUI        ();
        DrawContentGUI       ();
        DrawRenderPipelineGUI();

        SpriteEditorGUI.DrawGUI();
        ScriptEditorGUI.DrawGUI();
        ConsoleGUI     .DrawGUI();

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

    void Editor::DrawMainMenubar()
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Test compile"))
                {
                    std::string _output;
                    CompileScript("/Users/pengaki/Desktop/MeltSampleProject/Assets/Scripts/TestCustomSystem.cpp", _output);
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


                        CurrentWorkingProjectRootPath = outPath;


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
                    SpriteEditorGUI.Open();
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

    ImVec2 RemapImVec2(const ImVec2& value,
                       float originalMinX, float originalMaxX,
                       float targetMinX, float targetMaxX,
                       float originalMinY, float originalMaxY,
                       float targetMinY, float targetMaxY)
    {
        ImVec2 result;
        // Remap X component
        result.x = targetMinX + ((value.x - originalMinX) / (originalMaxX - originalMinX)) * (targetMaxX - targetMinX);
        // Remap Y component
        result.y = targetMinY + ((value.y - originalMinY) / (originalMaxY - originalMinY)) * (targetMaxY - targetMinY);
        return result;
    }

    void Editor::DrawSceneViewGUI()
    {
        MELT::Scene* _working_scene = Engine->manager_registry.get<MELT::SceneManager>()->working_scene;

        if (ImGui::Begin("Scene view"))
        {
            ImVec2 _cursorScreenPos = ImGui::GetCursorScreenPos();
            const float _sceneEditorWindowWidth  = ImGui::GetContentRegionAvail().x;
            const float _sceneEditorWindowHeight = ImGui::GetContentRegionAvail().y;

            ImGuizmo::SetOrthographic(true); // or true if using orthographic
            ImGuizmo::SetDrawlist();
            ImGuizmo::SetRect(_cursorScreenPos.x, _cursorScreenPos.y, _sceneEditorWindowWidth, _sceneEditorWindowHeight);

            if (ImGui::IsWindowHovered())
            {
                if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
                {
                    if (!ImGuizmo::IsOver() && !ImGuizmo::IsUsing() || !_working_scene->selected_node_id.has_value())
                    {
                        Engine->deselect_all_nodes();
                        Engine->SelectObject(MELT::Input.MouseScreenPosition, Engine->MainCamera);
                    }
                }
            }

            ImGui::GetWindowDrawList()->AddImage(
                    (void*)(intptr_t)Engine->manager_registry.get<MELT::RenderPipeline>()->editor_scene_frame_buffer->texture_id,
                    ImVec2(_cursorScreenPos.x, _cursorScreenPos.y),
                    ImVec2(_cursorScreenPos.x + _sceneEditorWindowWidth, _cursorScreenPos.y + _sceneEditorWindowHeight),
                    ImVec2(0, 1),
                    ImVec2(1, 0)
            );

            if (_working_scene->selected_node_id.has_value())
            {
                MELT::Node* _node = _working_scene->get_selected_node();

                auto& transform = _node->get_component<MELT::Transform>();

                glm::mat4 objectMatrix = transform.get_transform_matrix();

                ImGuizmo::Manipulate(
                    glm::value_ptr(Engine->MainCamera.GetViewMatrix()),
                    glm::value_ptr(Engine->MainCamera.GetOrthographicProjectionMatrix()),
                    ImGuizmo::TRANSLATE, ImGuizmo::WORLD,
                    glm::value_ptr(objectMatrix)
                );

                if (ImGuizmo::IsUsing())
                {
                    ImGuizmo::DecomposeMatrixToComponents(
                        glm::value_ptr(objectMatrix),
                        glm::value_ptr(transform.position),
                        glm::value_ptr(transform.rotation),
                        glm::value_ptr(transform.scale));
                }
            }

            Engine->MainCamera.WindowSize.x = _sceneEditorWindowWidth;
            Engine->MainCamera.WindowSize.y = _sceneEditorWindowHeight;
            Engine->MainCamera.UpdateScreenSizeWithOrthographicSize(_sceneEditorWindowWidth / _sceneEditorWindowHeight);

            MELT::Input.MouseWindowPosition.x = ImGui::GetMousePos().x;
            MELT::Input.MouseWindowPosition.y = ImGui::GetMousePos().y;
            MELT::Input.MouseScreenPosition.x = ImVec2(MELT::Input.MouseWindowPosition.x - _cursorScreenPos.x, MELT::Input.MouseWindowPosition.y - _cursorScreenPos.y).x;
            MELT::Input.MouseScreenPosition.y = ImVec2(MELT::Input.MouseWindowPosition.x - _cursorScreenPos.x, MELT::Input.MouseWindowPosition.y - _cursorScreenPos.y).y;


            ImVec2 _screenPos = ImVec2(MELT::Input.MouseWindowPosition.x - _cursorScreenPos.x, MELT::Input.MouseWindowPosition.y - _cursorScreenPos.y);
            ImVec2 _normalizedPos = RemapImVec2(_screenPos,
                                                0.0f, _sceneEditorWindowWidth , 0.0f, 1.0f,
                                                0.0f, _sceneEditorWindowHeight, 0.0f, 1.0f);

            ImVec2 _mouseWorldPos = RemapImVec2(_screenPos,
                                                0.0f, _sceneEditorWindowWidth , -Engine->MainCamera.HalfScreenWidth(),  Engine->MainCamera.HalfScreenWidth(),
                                                0.0f, _sceneEditorWindowHeight,  Engine->MainCamera.HalfScreenHeight(), -Engine->MainCamera.HalfScreenHeight());

            _mouseWorldPos.x += Engine->MainCamera.Position.x;
            _mouseWorldPos.y += Engine->MainCamera.Position.y;


            MELT::Input.MouseScreenNormalizedPosition.x = _normalizedPos.x;
            MELT::Input.MouseScreenNormalizedPosition.y = _normalizedPos.y;
            MELT::Input.MouseScreenWorldPosition.x      = _mouseWorldPos.x;
            MELT::Input.MouseScreenWorldPosition.y      = _mouseWorldPos.y;

            ImGui::Text("Window content          W H : (%.1f, %.1f)"     , _sceneEditorWindowWidth                    , _sceneEditorWindowHeight                   );
            ImGui::Text("Orthographic projection W H : (%.1f, %.1f)"     , Engine->MainCamera.ScreenSize.x            , Engine->MainCamera.ScreenSize.y            );
            ImGui::Text("Mouse window position       : (%.1f, %.1f)"     , MELT::Input.MouseWindowPosition .x         , MELT::Input.MouseWindowPosition .y         );
            ImGui::Text("Mouse screen position       : (%.1f, %.1f)"     , MELT::Input.MouseScreenPosition.x          , MELT::Input.MouseScreenPosition.y          );
            ImGui::Text("Normalized position         : (%.1f, %.1f)"     , MELT::Input.MouseScreenNormalizedPosition.x, MELT::Input.MouseScreenNormalizedPosition.y);
            ImGui::Text("Mouse world position        : (%.1f, %.1f)"     , MELT::Input.MouseScreenWorldPosition.x     , MELT::Input.MouseScreenWorldPosition.y     );
            ImGui::InputFloat3("Camera position", glm::value_ptr(Engine->MainCamera.Position));
            ImGui::SliderFloat("Near plane"       , &Engine->MainCamera.NearPlane, -100.0f, 0.0f);
            ImGui::SliderFloat("Far plane"        , &Engine->MainCamera.FarPlane, 0.0, 1000.0f);
            ImGui::SliderFloat("Orthographic size", &Engine->MainCamera.OrthographicSize, 1.0f, 200.f);
        }
        ImGui::End();
    }

    int _selectedItem = -1;

    void Editor::DrawHierarchyGUI()
    {
        //ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(33, 36, 35, 255));
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ChildBackground_Color);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10.0f, 10.0f));

        if (ImGui::Begin("Hierarchy"))
        {
            ImDrawList* drawList = ImGui::GetWindowDrawList();

            float windowWidth = ImGui::GetWindowWidth() - 20.0f;
            float windowHeight = 700.0f;

            ImVec2 childPos = ImGui::GetCursorScreenPos();
            ImVec2 childSize(windowWidth, windowHeight);
            float rounding = 10.0f;
            ImU32 fillColor = IM_COL32(8, 14, 15, 255);
            drawList->AddRectFilled(childPos, ImVec2(childPos.x + childSize.x, childPos.y + childSize.y), fillColor, rounding);

            if (ImGui::IsMouseClicked(ImGuiMouseButton_Right) &&!ImGui::IsAnyItemHovered() && ImGui::IsMouseHoveringRect(childPos, ImVec2(childPos.x + childSize.x, childPos.y + childSize.y)))
                ImGui::OpenPopup("CustomPopup");

            ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiCond_Always);

            ImGui::PushStyleColor(ImGuiCol_PopupBg, IM_COL32(73, 74, 70, 255));
            ImGui::PushStyleColor(ImGuiCol_Border , IM_COL32(73, 74, 70, 0));
            ImGui::PushStyleVar(ImGuiStyleVar_PopupRounding, 10.0f);
            if (ImGui::BeginPopup("CustomPopup"))
            {
                ImGui::Text("Object creation");
                ImGui::Separator();

                if (ImGui::MenuItem("Create entity"))
                {
                    Engine->CreateNode();
                }

                if (ImGui::MenuItem("Create scene")) {
                }
                if (ImGui::MenuItem("Create group")) {
                }
                ImGui::EndPopup();
            }
            ImGui::PopStyleColor(2);
            ImGui::PopStyleVar();

            ImGui::BeginChild("Scene window", childSize, false);

            ImGui::SetCursorPos(ImVec2(10.0f, 10.0f));
            ImGui::BeginChild("Tree window", ImVec2(childSize.x - 20.0f, childSize.y - 10.0f), false);

            ImGui::PushStyleColor(ImGuiCol_Header, IM_COL32(92, 97, 62, 255));
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f);

            bool any_selected = false;

            if (ImGui::CollapsingHeader("Scene 1"))
            {
                MELT::Scene* _working_scene = Engine->manager_registry.get<MELT::SceneManager>()->working_scene;
                for(std::size_t _i = 0; _i < _working_scene->get_all_nodes().size(); ++_i)
                {
                    auto& _node = _working_scene->get_all_nodes()[_i];

                    std::string _name = _node.name + std::to_string(_i);

                    if(ImGui::Selectable(_name.c_str(), _i == _selectedItem && _working_scene->selected_node_id.has_value()))
                    {
                        any_selected = true;

                        _selectedItem = _i;

                        _working_scene->deselect_all_nodes();
                        _working_scene->selected_node_id = _node.id;

                        _node.is_selected = true;
                    }
                }

                if (!any_selected &&
                   ImGui::IsWindowHovered() &&
                   !ImGui::IsAnyItemHovered() &&
                   ImGui::IsMouseClicked(ImGuiMouseButton_Left))
                {
                    _working_scene->deselect_all_nodes();
                    _selectedItem = -1;
                }
            }

            ImGui::PopStyleColor();
            ImGui::PopStyleVar();

            ImGui::EndChild();
            ImGui::EndChild();
        }
        ImGui::End();
        ImGui::PopStyleVar();
        ImGui::PopStyleColor();
    }

    MELT::Node* currentNodeRef;

    void Editor::DrawInspectorGUI()
    {
        MELT::Scene* _working_scene = Engine->manager_registry.get<MELT::SceneManager>()->working_scene;
        MELT::Node * _selected_node = _working_scene->get_selected_node();

        ImGui::PushStyleColor(ImGuiCol_WindowBg, ChildBackground_Color);
        if (ImGui::Begin("Inspector"))
        {
            ImDrawList* draw_list = ImGui::GetWindowDrawList();

            ImVec2 _startCursor = ImGui::GetCursorScreenPos();
            ImVec2 rect_min     = ImGui::GetCursorScreenPos();

            ImVec2 padding = ImGui::GetStyle().WindowPadding;
            rect_min.x -= padding.x;
            rect_min.y -= padding.y;

            ImVec2 rect_max = ImVec2(
                    rect_min.x + ImGui::GetWindowWidth(),
                    rect_min.y + 100);

            draw_list->AddRectFilled(
                    rect_min,
                    rect_max,
                    ChildBackground_Color);

            rect_min.y += 100.0f;

            rect_max.x = rect_min.x + ImGui::GetWindowWidth();
            rect_max.y = rect_min.y + 400.0f;

            rect_min.x += ImGui::GetStyle().WindowBorderSize + 1.0f;
            rect_max.x -= ImGui::GetStyle().WindowBorderSize + 1.0f;

            if (_selected_node)
            {
                char buffer[128];
                std::strncpy(buffer, _selected_node->name.c_str(), sizeof(buffer));
                buffer[sizeof(buffer) - 1] = '\0'; // ensure null termination
                if (ImGui::InputText("Name", buffer, IM_ARRAYSIZE(buffer)))
                    _selected_node->name = std::string(buffer);
                ImGui::Text(_selected_node->id.c_str());
            }

            ImGui::SetCursorScreenPos(rect_min);

            ImGui::NewLine();

            DrawLineSeparator();

            if (_selected_node && _selected_node->has_component<MELT::Transform>())
            {
                MELT::Transform& _transform = _selected_node->get_component<MELT::Transform>();
                DrawTransformComponentPanel(_transform);
                DrawLineSeparator();
            }

            if (_selected_node && _selected_node->has_component<MELT::MeshRenderer>())
            {
                MELT::MeshRenderer& _renderer = _selected_node->get_component<MELT::MeshRenderer>();
                DrawRendererComponentPanel(_renderer);
                DrawLineSeparator();
            }

            if (_selected_node && _selected_node->has_component<MELT::BoxCollider>())
            {
                MELT::BoxCollider& _box_collider = _selected_node->get_component<MELT::BoxCollider>();
                DrawBoxColliderComponentPanel(_box_collider);
                DrawLineSeparator();
            }

            //Add components button
            ImVec2 buttonSize = ImVec2(120, 30);
            ImVec2 windowSize = ImGui::GetWindowSize();
            ImGui::SetCursorPosY(windowSize.y - buttonSize.y - ImGui::GetStyle().WindowPadding.y);
            float buttonX = (windowSize.x - buttonSize.x) / 2.0f;
            ImGui::SetCursorPosX(buttonX);
            if (ImGui::Button("Add component", buttonSize))
            {
                ImGui::OpenPopup("AddComponentPopup");
            }

            ImGui::PushStyleColor(ImGuiCol_PopupBg, IM_COL32(73, 74, 70, 255));
            ImGui::PushStyleColor(ImGuiCol_Border , IM_COL32(73, 74, 70, 0));
            ImGui::PushStyleVar(ImGuiStyleVar_PopupRounding, 10.0f);
            if (ImGui::BeginPopup("AddComponentPopup"))
            {
                ImGui::Text("Components");
                ImGui::Separator();
                if (ImGui::MenuItem("Renderer"))
                {
                    if (_selected_node && !_selected_node->has_component<MELT::Renderer>())
                        _selected_node->add_component<MELT::Renderer>();
                }
                if (ImGui::MenuItem("Sprite Renderer"))
                {
                }

                if (ImGui::MenuItem("Box Collider"))
                {
                    if (_selected_node && !_selected_node->has_component<MELT::BoxCollider>())
                        _selected_node->add_component<MELT::BoxCollider>();
                }
                ImGui::EndPopup();
            }
            ImGui::PopStyleColor(2);
            ImGui::PopStyleVar();
        }
        ImGui::End();
        ImGui::PopStyleColor();
    }

    void Editor::DrawMaterialGUI()
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



            std::shared_ptr<MELT::RenderPipeline> _render_pipeline = Engine->manager_registry.get<MELT::RenderPipeline>();

            if (ImGui::ColorEdit4("##picker", &_render_pipeline->shader_preview.clear_color[0], ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel)) {
                // color changed!
            }

            float availableHeight = ImGui::GetContentRegionAvail().y;
            float windowWidth     = ImGui::GetContentRegionAvail().x;

            ImGui::Dummy(ImVec2(0, availableHeight - windowWidth)); // Push everything down

            ImVec2 imageSize(windowWidth, windowWidth); // Square: width == height
            //ImGui::Image((void*)(intptr_t)Engine->manager_registry.get<MELT::RenderPipeline>()->editor_scene_frame_buffer->texture_id, imageSize);

            ImGui::Image(Engine->manager_registry.get<MELT::RenderPipeline>()->shader_preview_texture(), imageSize);
        }
        ImGui::End();
        ImGui::PopStyleColor();
    }

    void Editor::DrawContentGUI()
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

    void Editor::DrawRenderPipelineGUI()
    {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ChildBackground_Color);
        if (ImGui::Begin("Render Pipeline"))
        {
            std::shared_ptr<MELT::RenderPipeline> _render_pipeline = Engine->manager_registry.get<MELT::RenderPipeline>();

            ImGui::ColorEdit4("Color with Alpha", &_render_pipeline->clear_color[0]);
        }
        ImGui::End();
        ImGui::PopStyleColor();
    }

    std::vector<const char*> items = {
            "Item 1", "Item 2", "Item 3", "Item 4",
            "Item 5", "Item 6", "Item 7", "Item 8",
            "Item 9", "Item 10", "Item 11", "Item 12"
    };

    void DisplayFileBrowser(const std::filesystem::path& path)
    {
        for (const auto& entry : std::filesystem::directory_iterator(path)) {

            std::string filename = entry.path().filename().string();

            if (filename == ".DS_Store")
                continue;

            if (entry.is_directory())
            {
                if (ImGui::TreeNode(entry.path().filename().string().c_str()))
                {
                    DisplayFileBrowser(entry.path());
                    ImGui::TreePop();
                }
            }
            else if (entry.is_regular_file())
            {
                if (ImGui::Selectable(entry.path().filename().string().c_str()))
                {
                    std::string selectedFile = entry.path().string();
                }
            }
        }
    }

    void Editor::DrawAssetsGUI()
    {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ChildBackground_Color);

        ImVec2 windowPadding(4.0f, 4.0f); // Adjust values as needed
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, windowPadding);
        ImGui::Begin("Project");



            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4.0f, 0));
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ChildBackground_Color);

            ImGui::BeginChild("Files", ImVec2(200, ImGui::GetContentRegionAvail().y), true);
            ImGui::Text("Files :");

            ImGui::BeginChild("##Scrollable List", ImVec2(0, ImGui::GetContentRegionAvail().y), true);

            if(std::filesystem::exists(CurrentWorkingProjectRootPath) && std::filesystem::is_directory(CurrentWorkingProjectRootPath))
            {
                DisplayFileBrowser(CurrentWorkingProjectRootPath);
            }

            ImGui::EndChild();
            ImGui::EndChild();
            ImGui::PopStyleColor();

            ImGui::SameLine();

            ImGui::PushStyleColor(ImGuiCol_ChildBg, ChildBackground_Color);

            ImGui::BeginChild("Child Window 2", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);


            MELT::TextureData* _texture_data = Engine->manager_registry.get<MELT::ResourceManager>()->get_texture_data("open-file.png");
            if (_texture_data)
            {
                ImTextureID folderIconTex = (ImTextureID)(intptr_t)_texture_data->p_texture->texture_id;

                ImGui::BeginGroup();

                    ImGui::PushStyleColor(ImGuiCol_Button,        ChildBackground_Color); // normal
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ChildBackground_Color); // hover
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(0.1f, 0.4f, 0.7f, 1.0f));

                    ImVec2 iconSize(64, 64);
                    ImVec2 uv0      = ImVec2(0.0f, 0.0f); // top-left
                    ImVec2 uv1      = ImVec2(1.0f, 1.0f); // bottom-right
                    ImVec4 bg_col   = ImVec4(0, 0, 0, 0); // transparent
                    ImVec4 tint_color = ImGui::IsItemHovered() ?
                        ImVec4(0.0f, 0.0f, 1.0f, 1.0f) :
                        ImVec4(1, 1, 1, 1);

                    if (ImGui::ImageButton(folderIconTex, iconSize, uv0, uv1, -1, bg_col, tint_color))
                    {

                    }
                    if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
                    {
                    }

                    const char* label = "My Folder";
                    ImVec2 textSize = ImGui::CalcTextSize(label);
                    float textOffset = (iconSize.x - textSize.x) * 0.5f;
                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + textOffset);
                    ImGui::TextUnformatted(label);

                    ImGui::PopStyleColor(3); // Pop all 3 colors
                ImGui::EndGroup();






            }



            ImGui::EndChild();
            ImGui::NewLine();


            ImGui::PopStyleColor();
            ImGui::PopStyleVar();


        ImGui::End();
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();
    }

    void Editor::DrawTransformComponentPanel(MELT::Transform& _transform)
    {
        if (ImGui::CollapsingHeader("Transform Component", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Text("Global");

            ImGui::Dummy(ImVec2(0.0f, 4.0f));

            ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0, 0, 0, 255));
            ImGui::Indent();

            auto _font_color = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);

            ImGui::PushStyleColor(ImGuiCol_Text, _font_color);
            ImGui::Text("Position");
            ImGui::PopStyleColor();
            ImGui::SameLine(120.0f);
            ImGui::InputFloat3("##Position", glm::value_ptr(_transform.position));

            ImGui::PushStyleColor(ImGuiCol_Text, _font_color);
            ImGui::Text("Rotation");
            ImGui::PopStyleColor();
            ImGui::SameLine(120.0f);
            ImGui::InputFloat3("##Rotation", glm::value_ptr(_transform.rotation));

            ImGui::PushStyleColor(ImGuiCol_Text, _font_color);
            ImGui::Text("Scale");
            ImGui::PopStyleColor();
            ImGui::SameLine(120.0f);
            ImGui::InputFloat3("##Scale", glm::value_ptr(_transform.scale));

            ImGui::Unindent();
            ImGui::PopStyleColor();

            ImGui::Text("Local");

            ImGui::Dummy(ImVec2(0.0f, 4.0f));

            ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0, 0, 0, 255));
            ImGui::Indent();

            // ImGui::PushStyleColor(ImGuiCol_Text, _font_color);
            // ImGui::Text("Position");
            // ImGui::PopStyleColor();
            // ImGui::SameLine(120.0f);
            // ImGui::InputFloat3("##Position", glm::value_ptr(_transform.position));
            //
            // ImGui::PushStyleColor(ImGuiCol_Text, _font_color);
            // ImGui::Text("Rotation");
            // ImGui::PopStyleColor();
            // ImGui::SameLine(120.0f);
            // ImGui::InputFloat3("##Rotation", glm::value_ptr(_transform.rotation));
            //
            // ImGui::PushStyleColor(ImGuiCol_Text, _font_color);
            // ImGui::Text("Scale");
            // ImGui::PopStyleColor();
            // ImGui::SameLine(120.0f);
            // ImGui::InputFloat3("##Scale", glm::value_ptr(_transform.scale));

            ImGui::Unindent();
            ImGui::PopStyleColor();

            ImGui::Dummy(ImVec2(0.0f, 4.0f));
        }
    }

    void Editor::DrawRendererComponentPanel(MELT::MeshRenderer& _renderer)
    {
        MELT::Scene* _working_scene = Engine->manager_registry.get<MELT::SceneManager>()->working_scene;
        MELT::Node * _selected_node = _working_scene->get_selected_node();

        if (ImGui::CollapsingHeader("Renderer Component", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Dummy(ImVec2(0.0f, 4.0f));

            ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0, 0, 0, 255));

                auto _font_color = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);

                ImGui::Text("Mesh");
                ImGui::SameLine(120.0f);
                ImGui::Text("name : %s", _renderer.mesh_data->name.c_str());
                ImGui::Text("");
                ImGui::SameLine(120.0f);
                ImGui::Text("uuid : %s", _renderer.mesh_data->uuid.c_str());

                ImGui::Indent();
                ImGui::PushStyleColor(ImGuiCol_Text, _font_color);

                    ImGui::Text("vertices");
                    ImGui::SameLine(120.0f);
                    //ImGui::Text(std::to_string(_renderer.get_mesh_ref().vertices.size()).c_str());
                    ImGui::Text(std::to_string(_renderer.mesh_data->mesh->vertices.size()).c_str());

                    ImGui::Text("indices");
                    ImGui::SameLine(120.0f);
                    ImGui::Text(std::to_string(_renderer.mesh_data->mesh->indices.size()).c_str());

                ImGui::PopStyleColor();
                ImGui::Unindent();

                ImGui::Text("Material");

                ImGui::Indent();
                // ImGui::PushStyleColor(ImGuiCol_Text, _font_color);
                // ImGui::PopStyleColor();

                ImGui::Unindent();

            ImGui::PopStyleColor();


            // Push custom colors for button
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f);
            ImGui::PushStyleColor(ImGuiCol_Button,        IM_COL32(40, 40, 40, 255));  // Default
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(100, 100, 100, 255));  // Hover
            ImGui::PushStyleColor(ImGuiCol_ButtonActive,  IM_COL32(200, 200, 200, 255));    // Pressed

            ImGui::NewLine();
            ImGui::SameLine(ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize("Delete").x - ImGui::GetStyle().FramePadding.x * 2);
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
            if (ImGui::Button("Delete 0")) {
                if (_selected_node && _selected_node->has_component<MELT::MeshRenderer>())
                    _selected_node->remove_component<MELT::MeshRenderer>();
            }
            ImGui::PopStyleColor();

            // Pop them in reverse order
            ImGui::PopStyleColor(3);
            ImGui::PopStyleVar();

            ImGui::Dummy(ImVec2(0.0f, 4.0f));
        }
    }

    void Editor::DrawBoxColliderComponentPanel(MELT::BoxCollider& _box_collider)
    {
        MELT::Scene* _working_scene = Engine->manager_registry.get<MELT::SceneManager>()->working_scene;
        MELT::Node * _selected_node = _working_scene->get_selected_node();

        if (ImGui::CollapsingHeader("Box Collider 3D Component", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Dummy(ImVec2(0.0f, 4.0f));

            ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0, 0, 0, 255));
            ImGui::Indent();

            auto _font_color = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);

            ImGui::PushStyleColor(ImGuiCol_Text, _font_color);
            ImGui::Text("Mesh");
            ImGui::PopStyleColor();

            ImGui::PushStyleColor(ImGuiCol_Text, _font_color);
            ImGui::Text("Material");
            ImGui::PopStyleColor();

            ImGui::Unindent();
            ImGui::PopStyleColor();


            // Push custom colors for button
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f);
            ImGui::PushStyleColor(ImGuiCol_Button,        IM_COL32(40, 40, 40, 255));  // Default
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(100, 100, 100, 255));  // Hover
            ImGui::PushStyleColor(ImGuiCol_ButtonActive,  IM_COL32(200, 200, 200, 255));    // Pressed

            ImGui::NewLine();
            ImGui::SameLine(ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize("Delete").x - ImGui::GetStyle().FramePadding.x * 2);
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
            if (ImGui::Button("Delete 1")) {
                if (_selected_node && _selected_node->has_component<MELT::BoxCollider>())
                    _selected_node->remove_component<MELT::BoxCollider>();
            }
            ImGui::PopStyleColor();

            // Pop them in reverse order
            ImGui::PopStyleColor(3);
            ImGui::PopStyleVar();

            ImGui::Dummy(ImVec2(0.0f, 4.0f));
        }
    }

    void Editor::DrawSpriteRendererComponentPanel(MELT::SpriteRenderer &_spriteRenderer)
    {
        const float _panelWidth  = ImGui::GetContentRegionAvail().x;
        const float _panelHeight = 100.0f;

        ImDrawList* _drawList = ImGui::GetWindowDrawList();
        ImGuiStyle& _style    = ImGui::GetStyle();

        ImVec2 _panelOriginPos = ImGui::GetCursorScreenPos();
        ImVec2 _panelSize (_panelWidth, _panelHeight);

        _drawList->AddRectFilled(
                _panelOriginPos,
                ImVec2(_panelOriginPos.x + _panelSize.x, _panelOriginPos.y + _panelSize.y),
                IM_COL32(28, 31, 29, 255), 6.0f);

        _drawList->AddRectFilled(
                _panelOriginPos,
                ImVec2(_panelOriginPos.x + _panelSize.x, _panelOriginPos.y + ImGui::GetFrameHeight()),
                IM_COL32(61, 63, 66, 255), 0.0f);

        ImGui::SetCursorScreenPos(ImVec2(_panelOriginPos.x + _style.FramePadding.x, _panelOriginPos.y + _style.FramePadding.y));

        ImGui::SetWindowFontScale(0.75f);
        ImGui::Text(ICON_KI_RADIO);
        ImGui::SetWindowFontScale(1.0f);
        ImGui::SameLine();
        ImGui::Text("Transform component");

        ImGui::SetCursorScreenPos(ImVec2(_panelOriginPos.x + _panelWidth - 40.0f, _panelOriginPos.y));

        ImGui::PushStyleColor(ImGuiCol_Button       , IM_COL32(61, 63, 66, 255));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive , ImVec4(0.6f, 0.6f, 0.6f, 1.0f));

        if(ImGui::Button(ICON_KI_MINUS, ImVec2(40, ImGui::GetFrameHeight())))
        {
        }
        ImGui::PopStyleColor(3);

        ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0, 0, 0, 255));
        ImGui::Indent();
        ImGui::Text("Texture source");

        auto& _textureData = Engine->TextureMng.TextureDataTable["blacknwhite"];
        std::vector<const char*> textureKeys;
        textureKeys.reserve(_textureData.SpriteDataMap.size());
        for (const auto& pair : _textureData.SpriteDataMap) {
            textureKeys.push_back(pair.first.c_str());
        }

        static int currentItem = 0;  // Index of the current selected item

        ImGui::Text("Sprite");
        ImGui::SameLine(120.0f);



        if (ImGui::Combo("##Sprite", &currentItem, textureKeys.data(), (int)textureKeys.size()))
        {
            std::cout << "sladj;" << std::endl;
        }




        ImGui::Unindent();
        ImGui::PopStyleColor();

        ImGui::SetCursorScreenPos(ImVec2(
                _panelOriginPos.x,
                _panelOriginPos.y + _panelHeight + _style.ItemSpacing.y));
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
        YAML::Node _root;

        _root["Scene"] = "Test";

        std::ofstream _file;
        _file.open(SCENE_PATH);
        _file << _root;
        _file.close();
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

    void Editor::DrawLineSeparator()
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

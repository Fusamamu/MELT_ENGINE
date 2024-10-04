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

        // Load a custom font from a .ttf file
        //io.Fonts->AddFontFromFileTTF("../MeltEngineEditorLib/res/fonts/comfortaa/Comfortaa-Regular.ttf", 13.0f); // Example font size: 18
        io.Fonts->AddFontFromFileTTF("../MeltEngineEditorLib/res/fonts/JetBrainsMono-1.0.2/ttf/JetBrainsMono-Regular.ttf", 15.0f); // Example font size: 18



        ImGuiStyle& style = ImGui::GetStyle();

        ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(8.0f/255.0f, 14.0f/255.0f, 15.0f/255.0f, 1.0f);  // Set to a custom color (RGBA)


        style.Colors[ImGuiCol_TitleBg]        = ImVec4(33.0f/255.0f, 36.0f/255.0f, 35.0f/255.0f, 1.0f);
        style.Colors[ImGuiCol_TitleBgActive]  = ImVec4(61.0f/255.0f, 53.0f/255.0f, 40.0f/255.0f, 1.0f);

        style.Colors[ImGuiCol_Border]        = ImVec4(33.0f/255.0f, 36.0f/255.0f, 35.0f/255.0f, 1.0f);
        style.Colors[ImGuiCol_BorderShadow]  = ImVec4(33.0f/255.0f, 36.0f/255.0f, 35.0f/255.0f, 1.0f);

        style.Colors[ImGuiCol_Header]     = ImVec4(33.0f/255.0f, 36.0f/255.0f, 35.0f/255.0f, 1.0f);
        style.Colors[ImGuiCol_HeaderHovered]     = ImVec4(172.0f/255.0f, 184.0f/255.0f, 39.0f/255.0f, 1.0f);
        style.Colors[ImGuiCol_HeaderActive]     = ImVec4(172.0f/255.0f, 184.0f/255.0f, 39.0f/255.0f, 1.0f);
        style.Colors[ImGuiCol_Separator]  = ImVec4(33.0f/255.0f, 36.0f/255.0f, 35.0f/255.0f, 1.0f);

        style.Colors[ImGuiCol_FrameBgActive]        = ImVec4(255.0f/255.0f, 255.0f/255.0f, 255.0f/255.0f, 1.0f);

        style.Colors[ImGuiCol_Tab]                  = ImVec4(59.0f/255.0f, 53.0f/255.0f, 51.0f/255.0f, 1.0f);
        style.Colors[ImGuiCol_TabActive]            = ImVec4(230.0f/255.0f, 150.0f/255.0f, 30.0f/255.0f, 1.0f);

        style.Colors[ImGuiCol_TabUnfocusedActive]   = ImVec4(59.0f/255.0f, 53.0f/255.0f, 51.0f/255.0f, 1.0f);
        style.Colors[ImGuiCol_TabUnfocused]         = ImVec4(59.0f/255.0f, 53.0f/255.0f, 51.0f/255.0f, 1.0f);
        style.Colors[ImGuiCol_TabHovered]           = ImVec4(232.0f/255.0f, 194.0f/255.0f, 58.0f/255.0f, 1.0f);
        style.Colors[ImGuiCol_TabSelectedOverline]  = ImVec4(59.0f/255.0f, 53.0f/255.0f, 51.0f/255.0f, 0.0f);

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

            ImDrawList* _drawList = ImGui::GetWindowDrawList();

            ImVec2 _panelPos = ImGui::GetCursorScreenPos();
            ImVec2 _panelSize (ImGui::GetWindowWidth() - 20.0f, 100.0f);

            _drawList->AddRectFilled(
                    _panelPos,
                    ImVec2(_panelPos.x + _panelSize.x, _panelPos.y + _panelSize.y),
                    IM_COL32(28, 31, 29, 255), 6.0f);


            _drawList->AddRectFilled(
                    _panelPos,
                    ImVec2(_panelPos.x + _panelSize.x, _panelPos.y + ImGui::GetTextLineHeight() + 5.0f),
                    IM_COL32(61, 63, 66, 255), 0.0f);

            ImVec2 text_size = ImGui::CalcTextSize("Text");
            ImVec2 text_position = _panelPos;

            _drawList->AddText(text_position, IM_COL32(0, 0, 0, 255), "Transform component"); // Change color as needed

            _panelPos.y += 100.0f + 10.0f;


            _drawList->AddRectFilled(
                    _panelPos,
                    ImVec2(_panelPos.x + _panelSize.x, _panelPos.y + _panelSize.y),
                    IM_COL32(28, 31, 29, 255), 6.0f);


            _drawList->AddRectFilled(
                    _panelPos,
                    ImVec2(_panelPos.x + _panelSize.x, _panelPos.y + ImGui::GetTextLineHeight() + 5.0f),
                    IM_COL32(61, 63, 66, 255), 0.0f);

            text_position = _panelPos;

            _drawList->AddText(text_position, IM_COL32(0, 0, 0, 255), "Transform component"); // Change color as needed


//            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
//            ImDrawList* draw_list = ImGui::GetWindowDrawList();
//
//            // Get the cursor position (top-left corner where we want to start drawing)
//            ImVec2 p = ImGui::GetWindowPos();
//
//
//            const ImGuiStyle& style = ImGui::GetStyle();
//
//            // Get the height of the tab bar
//            float tab_bar_height = style.FramePadding.y;
//            p.y += tab_bar_height;
//
//            // Get the available width of the window
//            float window_width = ImGui::GetWindowWidth();
//
//            // Define a fixed height for the rectangle
//            float rect_height = 50.0f;
//
//            // Draw a rectangle that covers the full width of the window
//            draw_list->AddRectFilled(p, ImVec2(p.x + window_width, p.y + rect_height),
//                                     IM_COL32(100, 150, 250, 255));
//
//            ImGui::PopStyleVar();




//            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f);
//            if (ImGui::CollapsingHeader("Transform component"))
//            {
//                //ImGui::PushStyleVar(ImGuiCol_Bg, 6.0f);
//
//                ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 6.0f);
//                ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(28, 31, 29, 255));
//
//                //ImGui::BeginChild("Transform inspector", ImVec2(0, 200), true);
//
//                //ImGui::Text("Transform component");
//                ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0, 0, 0, 255));
//
//                static float _position[3] = { 0.0f, 0.0f, 0.0f };
//                static float _rotation[3] = { 0.0f, 0.0f, 0.0f };
//                static float _scale   [3] = { 0.0f, 0.0f, 0.0f };
//
//                ImGui::Text("Position");
//                ImGui::SameLine(120.0f);
//                ImGui::InputFloat3("", _position);
//                ImGui::Text("Rotation");
//                ImGui::SameLine(120.0f);
//                ImGui::InputFloat3("", _rotation);
//                ImGui::Text("Scale");
//                ImGui::SameLine(120.0f);
//                ImGui::InputFloat3("", _scale);
//
//                ImGui::PopStyleColor();
//                //ImGui::EndChild();
//
//                ImGui::PopStyleVar(2);
//                ImGui::PopStyleColor();
//
//            }
//            else
//            {
//                ImGui::PopStyleVar();
//            }

//            if (ImGui::Selectable("Selectable Rectangle", false, ImGuiSelectableFlags_AllowDoubleClick))
//            {
//                // Logic for when the rectangle is selected
//            }
//
//            int aa = 0;
//
//            if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
//            {
//                ImGui::SetDragDropPayload("ITEM_REORDER", &aa, sizeof(int)); // Set the drag payload as the item's index
//                ImGui::Text("Dragging %s", "slkdjalkf");  // Display the item being dragged
//                ImGui::EndDragDropSource();
//            }

//           static std::vector<std::string> items = {"Item 1", "Item 2", "Item 3", "Item 4"};
//            for (int i = 0; i < items.size(); i++)
//            {
//                // Unique ID for each item
//                ImGui::PushID(i);
//
//                if (ImGui::CollapsingHeader(items[i].c_str()))
//                {
//                    ImGui::Text("Content for %s", items[i].c_str());
//                }
//
//                // Handle dragging
//                if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
//                {
//                    ImGui::SetDragDropPayload("ITEM_REORDER", &i, sizeof(int)); // Set the drag payload as the item's index
//                    ImGui::Text("Dragging %s", items[i].c_str());  // Display the item being dragged
//                    ImGui::EndDragDropSource();
//                }
//
//                // Handle dropping
//                if (ImGui::BeginDragDropTarget())
//                {
//                    if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ITEM_REORDER"))
//                    {
//                        int dragged_index = *(const int*)payload->Data;
//
//                        // Swap the items
//                        if (dragged_index != i)
//                        {
//                            std::swap(items[dragged_index], items[i]);
//                        }
//                    }
//                    ImGui::EndDragDropTarget();
//                }
//
//                ImGui::PopID();
//            }

        }
        ImGui::End();






        ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(33, 36, 35, 255));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10.0f, 10.0f));  // Increase padding (x, y)
        if (ImGui::Begin("Hierarchy"))
        {
            ImDrawList* drawList = ImGui::GetWindowDrawList();

            float windowWidth = ImGui::GetWindowWidth() - 20.0f;
            float windowHeight = 700.0f;

            // Define position and size for the child window
            ImVec2 childPos = ImGui::GetCursorScreenPos();  // Position relative to the parent window
            ImVec2 childSize(windowWidth, windowHeight);                      // Size of the child window
            float rounding = 10.0f;                          // Rounding radius
            ImU32 fillColor = IM_COL32(8, 14, 15, 255); // Background color (white)
            ImU32 borderColor = IM_COL32(0, 0, 0, 255);     // Border color (black)



            drawList->AddRectFilled(childPos, ImVec2(childPos.x + childSize.x, childPos.y + childSize.y), fillColor, rounding);


            if (ImGui::IsMouseReleased(1) && ImGui::IsMouseHoveringRect(childPos, ImVec2(childPos.x + childSize.x, childPos.y + childSize.y))) {
                ImGui::OpenPopup("CustomPopup");
            }



            ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiCond_Always);
            ImGui::PushStyleColor(ImGuiCol_PopupBg, IM_COL32(73, 74, 70, 255));
            ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(73, 74, 70, 0));
            ImGui::PushStyleVar(ImGuiStyleVar_PopupRounding, 10.0f);

            if (ImGui::BeginPopup("CustomPopup")) {


                ImGui::Text("Object creation");
                ImGui::Separator(); // Add a separator

                if (ImGui::MenuItem("Create entity")) {
                    // Action for Option 2
                }
                if (ImGui::MenuItem("Create scene")) {
                    // Handle Property 1 action
                }

                if (ImGui::MenuItem("Create group")) {
                    // Action for Option 1
                }
                ImGui::PopStyleColor(2);
                ImGui::PopStyleVar(); // Restore previous style variable
                ImGui::EndPopup();
            }else
            {
                ImGui::PopStyleColor(2);
                ImGui::PopStyleVar(); // Restore previous style variable
            }



            ImGui::BeginChild("Scene window", childSize, false);



                const float padding = 10.0f; // Define your padding
                ImGui::SetCursorPos(ImVec2(padding, padding));
                ImGui::BeginChild("Tree window", ImVec2(childSize.x - 20.0f, childSize.y - 10.0f), false);

                ImGui::PushStyleColor(ImGuiCol_Header, IM_COL32(92, 97, 62, 255));
                ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f);
                if (ImGui::CollapsingHeader("Scene 1")) {

                    ImGui::PopStyleColor();
                    if (ImGui::TreeNodeEx("Root", ImGuiTreeNodeFlags_Selected)) {
                        // If the root node is clicked, you can handle the selection logic here
                        if (ImGui::IsItemClicked()) {
                            ImGui::Text("Root selected");
                        }

                        // Create a sub-tree node that is also selectable
                        if (ImGui::TreeNodeEx("Sub-Tree", ImGuiTreeNodeFlags_Selected)) {
                            // Handle selection logic for the sub-tree
                            if (ImGui::IsItemClicked()) {
                                ImGui::Text("Sub-Tree selected");
                            }

                            // Selectable items within the sub-tree
                            if (ImGui::Selectable("Selectable 1")) {
                                ImGui::Text("Selectable 1 clicked");
                            }
                            if (ImGui::Selectable("Selectable 2")) {
                                ImGui::Text("Selectable 2 clicked");
                            }

                            ImGui::TreePop();  // Close the sub-tree
                        }

                        ImGui::TreePop();  // Close the root
                    }
                }else
                {
                    ImGui::PopStyleColor();
                }
                ImGui::PopStyleVar();



            ImGui::PushStyleColor(ImGuiCol_Header, IM_COL32(92, 97, 62, 255));
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f);
            if (ImGui::CollapsingHeader("Scene 2")) {

                ImGui::PopStyleColor();
                if (ImGui::TreeNodeEx("Root", ImGuiTreeNodeFlags_Selected)) {
                    // If the root node is clicked, you can handle the selection logic here
                    if (ImGui::IsItemClicked()) {
                        ImGui::Text("Root selected");
                    }

                    // Create a sub-tree node that is also selectable
                    if (ImGui::TreeNodeEx("Sub-Tree", ImGuiTreeNodeFlags_Selected)) {
                        // Handle selection logic for the sub-tree
                        if (ImGui::IsItemClicked()) {
                            ImGui::Text("Sub-Tree selected");
                        }

                        // Selectable items within the sub-tree
                        if (ImGui::Selectable("Selectable 1")) {
                            ImGui::Text("Selectable 1 clicked");
                        }
                        if (ImGui::Selectable("Selectable 2")) {
                            ImGui::Text("Selectable 2 clicked");
                        }

                        ImGui::TreePop();  // Close the sub-tree
                    }

                    ImGui::TreePop();  // Close the root
                }
            }else
            {
                ImGui::PopStyleColor();
            }
            ImGui::PopStyleVar();



                ImGui::EndChild();  // Close child window
            ImGui::EndChild();  // Close child window











            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f);
            if (ImGui::CollapsingHeader("Scene 1")) {

                if (ImGui::TreeNodeEx("Root", ImGuiTreeNodeFlags_Selected)) {
                    // If the root node is clicked, you can handle the selection logic here
                    if (ImGui::IsItemClicked()) {
                        ImGui::Text("Root selected");
                    }

                    // Create a sub-tree node that is also selectable
                    if (ImGui::TreeNodeEx("Sub-Tree", ImGuiTreeNodeFlags_Selected)) {
                        // Handle selection logic for the sub-tree
                        if (ImGui::IsItemClicked()) {
                            ImGui::Text("Sub-Tree selected");
                        }

                        // Selectable items within the sub-tree
                        if (ImGui::Selectable("Selectable 1")) {
                            ImGui::Text("Selectable 1 clicked");
                        }
                        if (ImGui::Selectable("Selectable 2")) {
                            ImGui::Text("Selectable 2 clicked");
                        }

                        ImGui::TreePop();  // Close the sub-tree
                    }

                    ImGui::TreePop();  // Close the root
                }
            }
            ImGui::PopStyleVar();

        }
        ImGui::End();
        ImGui::PopStyleVar();
        ImGui::PopStyleColor();





        ImGui::ShowDemoWindow(); // Show demo window! :)

        if (ImGui::Begin("Scene view"))
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

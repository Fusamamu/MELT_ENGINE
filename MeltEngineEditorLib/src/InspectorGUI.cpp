#include "InspectorGUI.h"
#include "MeltEngineEditor.h"

namespace MELT_EDITOR
{
    InspectorGUI::InspectorGUI()
    {

    }

    void InspectorGUI::init(Editor* _editor)
    {
        m_editor = _editor;
        m_engine = _editor->engine;
    }

    void InspectorGUI::draw_gui()
    {
        unsigned int ChildBackground_Color  = IM_COL32(26, 28, 27, 255);

        MELT::Scene* _working_scene = m_engine->manager_registry.get<MELT::SceneManager>()->working_scene;

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

            m_editor->draw_line_separator();

            if (_selected_node && _selected_node->has_component<MELT::Transform>())
            {
                MELT::Transform& _transform = _selected_node->get_component<MELT::Transform>();
                draw_transform_component_panel(_transform);
                m_editor->draw_line_separator();
            }

            if (_selected_node && _selected_node->has_component<MELT::MeshRenderer>())
            {
                MELT::MeshRenderer& _renderer = _selected_node->get_component<MELT::MeshRenderer>();
                draw_renderer_component_panel(_renderer);
                m_editor->draw_line_separator();
            }

            if (_selected_node && _selected_node->has_component<MELT::BoxCollider>())
            {
                MELT::BoxCollider& _box_collider = _selected_node->get_component<MELT::BoxCollider>();
                draw_box_collider_component_panel(_box_collider);
                m_editor->draw_line_separator();
            }

            if (_selected_node && _selected_node->has_component<MELT::Camera>())
            {
                MELT::Camera& _camera = _selected_node->get_component<MELT::Camera>();
                draw_camera_component_panel(_camera);
                m_editor->draw_line_separator();
            }

            if (_selected_node && _selected_node->has_component<MELT::Light>())
            {
                MELT::Light& _light = _selected_node->get_component<MELT::Light>();
                draw_light_component_panel(_light);
                m_editor->draw_line_separator();
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

    void InspectorGUI::draw_transform_component_panel(MELT::Transform& _transform)
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

    void InspectorGUI::draw_renderer_component_panel(MELT::MeshRenderer& _renderer)
    {
        MELT::Scene* _working_scene = m_engine->manager_registry.get<MELT::SceneManager>()->working_scene;
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
                    //ImGui::Text(std::to_string(_renderer.mesh_data->mesh->vertices.size()).c_str());
                    ImGui::Text(std::to_string(_renderer.mesh_data->mesh->vertex_buffer.size()).c_str());

                    ImGui::Text("indices");
                    ImGui::SameLine(120.0f);
                    ImGui::Text(std::to_string(_renderer.mesh_data->mesh->index_buffer.size()).c_str());

                ImGui::PopStyleColor();
                ImGui::Unindent();



                ImGui::PushStyleColor(ImGuiCol_Button,        IM_COL32(40, 40, 40, 255));  // Default
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(100, 100, 100, 255));  // Hover
                ImGui::PushStyleColor(ImGuiCol_ButtonActive,  IM_COL32(200, 200, 200, 255));    // Pressed

                    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f);
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
                    if (ImGui::Button(" > ")) {
                        ImGui::OpenPopup("Search mesh ref");
                    }



                    ImGui::PushStyleColor(ImGuiCol_PopupBg, IM_COL32(73, 74, 70, 255));
                    ImGui::PushStyleColor(ImGuiCol_Border , IM_COL32(73, 74, 70, 0));
                    ImGui::PushStyleVar(ImGuiStyleVar_PopupRounding, 10.0f);
                    if (ImGui::BeginPopup("Search mesh ref"))
                    {
                        ImGui::Text("Mesh selection");
                        ImGui::Separator();



                        if (ImGui::BeginListBox("##listbox", ImVec2(200, 150)))
                        {
                            static int selected = -1;
                            for (int i = 0; i < 20; i++)
                            {
                                char label[32];
                                sprintf(label, "Item %d", i);
                                bool is_selected = (selected == i);
                                if (ImGui::Selectable(label, is_selected))
                                    selected = i;
                            }
                            ImGui::EndListBox();
                        }

                        ImGui::EndPopup();
                    }
                    ImGui::PopStyleColor(2);
                    ImGui::PopStyleVar();















                    ImGui::PopStyleColor();
                    ImGui::PopStyleVar();

                    ImGui::SameLine();

                    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f);
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
                    if (ImGui::Button(" selected mesh ")) {

                    }
                    ImGui::PopStyleColor();
                    ImGui::PopStyleVar();

                ImGui::PopStyleColor(3);






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

    void InspectorGUI::draw_box_collider_component_panel(MELT::BoxCollider& _box_collider)
    {
        MELT::Scene* _working_scene = m_engine->manager_registry.get<MELT::SceneManager>()->working_scene;
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

    void InspectorGUI::draw_sprite_renderer_component_panel(MELT::SpriteRenderer &_spriteRenderer)
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

        auto& _textureData = m_engine->texture_manager.TextureDataTable["blacknwhite"];
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

    void InspectorGUI::draw_camera_component_panel(MELT::Camera &_camera)
    {
        MELT::Scene* _working_scene = m_engine->manager_registry.get<MELT::SceneManager>()->working_scene;
        MELT::Node * _selected_node = _working_scene->get_selected_node();

        if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Dummy(ImVec2(0.0f, 4.0f));

            ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0, 0, 0, 255));
            ImGui::Indent();

            auto _font_color = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);

            // ImGui::PushStyleColor(ImGuiCol_Text, _font_color);
            // ImGui::Text("Orthographic");
            // ImGui::PopStyleColor();
            // ImGui::SameLine(120.0f);
            // ImGui::Checkbox("##UseOrtho", &_camera.use_orthographic);

            MELT_GUI::check_box("Orthographic", &_camera.use_orthographic);

            ImGui::PushStyleColor(ImGuiCol_Text, _font_color);
            ImGui::Text("Orthographic size");
            ImGui::PopStyleColor();
            ImGui::SameLine(120.0f);
            ImGui::InputFloat("##OrthographicSize", &_camera.orthographic_size);

            ImGui::PushStyleColor(ImGuiCol_Text, _font_color);
            ImGui::Text("Screen ratio");
            ImGui::PopStyleColor();
            ImGui::SameLine(120.0f);
            ImGui::InputFloat("##ScreenRatio", &_camera.screen_ratio);

            ImGui::PushStyleColor(ImGuiCol_Text, _font_color);
            ImGui::Text("Position");
            ImGui::PopStyleColor();
            ImGui::SameLine(120.0f);
            ImGui::InputFloat3("##CameraPosition", glm::value_ptr(_camera.position));

            ImGui::PushStyleColor(ImGuiCol_Text, _font_color);
            ImGui::Text("Target");
            ImGui::PopStyleColor();
            ImGui::SameLine(120.0f);
            ImGui::InputFloat3("##Target", glm::value_ptr(_camera.Target));

            ImGui::PushStyleColor(ImGuiCol_Text, _font_color);
            ImGui::Text("Near plane");
            ImGui::PopStyleColor();
            ImGui::SameLine(120.0f);
            ImGui::InputFloat("##NearPlane", &_camera.near_plane);

            ImGui::PushStyleColor(ImGuiCol_Text, _font_color);
            ImGui::Text("Far plane");
            ImGui::PopStyleColor();
            ImGui::SameLine(120.0f);
            ImGui::InputFloat("##FarPlane", &_camera.far_plane);

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
                if (_selected_node && _selected_node->has_component<MELT::Camera>())
                    _selected_node->remove_component<MELT::Camera>();
            }
            ImGui::PopStyleColor();

            ImGui::PopStyleColor(3);
            ImGui::PopStyleVar();

            ImGui::Dummy(ImVec2(0.0f, 4.0f));
        }
    }

    void InspectorGUI::draw_light_component_panel(MELT::Light &_light)
    {
        MELT::Scene* _working_scene = m_engine->manager_registry.get<MELT::SceneManager>()->working_scene;
        MELT::Node * _selected_node = _working_scene->get_selected_node();

        if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Dummy(ImVec2(0.0f, 4.0f));

            ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0, 0, 0, 255));
            ImGui::Indent();

            auto _font_color = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);





            ImGui::PushStyleColor(ImGuiCol_Text, _font_color);
            ImGui::Text("Color");
            ImGui::PopStyleColor();
            ImGui::SameLine(120.0f);
            ImGui::InputFloat3("##Color", glm::value_ptr(_light.color));



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
                if (_selected_node && _selected_node->has_component<MELT::Camera>())
                    _selected_node->remove_component<MELT::Camera>();
            }
            ImGui::PopStyleColor();

            ImGui::PopStyleColor(3);
            ImGui::PopStyleVar();

            ImGui::Dummy(ImVec2(0.0f, 4.0f));
        }
    }
}
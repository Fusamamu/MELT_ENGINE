#include "SceneViewGUI.h"
#include "MeltEngineEditor.h"

namespace MELT_EDITOR
{
    SceneViewGUI::SceneViewGUI()
    {

    }

    void SceneViewGUI::init(Editor* _editor)
    {
        m_editor = _editor;
        m_engine = _editor->engine;
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

    void SceneViewGUI::draw_gui()
    {
        MELT::Scene* _working_scene = m_engine->manager_registry.get<MELT::SceneManager>()->working_scene;

        if (ImGui::Begin("Scene view"))
        {
            ImVec2 _cursor_screen_pos = ImGui::GetCursorScreenPos();
            const float _scene_editor_window_width  = ImGui::GetContentRegionAvail().x;
            const float _scene_editor_window_height = ImGui::GetContentRegionAvail().y;

            ImGuizmo::SetOrthographic(true); // or true if using orthographic
            ImGuizmo::SetDrawlist();
            ImGuizmo::SetRect(_cursor_screen_pos.x, _cursor_screen_pos.y, _scene_editor_window_width, _scene_editor_window_height);

            if (ImGui::IsWindowHovered())
            {
                if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
                {
                    if (!ImGuizmo::IsOver() && !ImGuizmo::IsUsing() || !_working_scene->selected_node_id.has_value())
                    {
                        m_engine->deselect_all_nodes();
                        m_engine->select_object(MELT::Input.MouseScreenPosition, m_engine->MainCamera);
                    }
                }
            }

            ImGui::GetWindowDrawList()->AddImage(
                    (void*)(intptr_t)m_engine->manager_registry.get<MELT::RenderPipeline>()->editor_scene_frame_buffer->texture_id,
                    ImVec2(_cursor_screen_pos.x, _cursor_screen_pos.y),
                    ImVec2(_cursor_screen_pos.x + _scene_editor_window_width, _cursor_screen_pos.y + _scene_editor_window_height),
                    ImVec2(0, 1),
                    ImVec2(1, 0)
            );

            static ImGuizmo::OPERATION currentOperation = ImGuizmo::TRANSLATE;

            if (ImGui::Button("Translate"))
                currentOperation = ImGuizmo::TRANSLATE;
            ImGui::SameLine();
            if (ImGui::Button("Rotate"))
                currentOperation = ImGuizmo::ROTATE;
            ImGui::SameLine();
            if (ImGui::Button("Scale"))
                currentOperation = ImGuizmo::SCALE;

            if (_working_scene->selected_node_id.has_value())
            {
                MELT::Node* _node = _working_scene->get_selected_node();

                auto& transform = _node->get_component<MELT::Transform>();

                glm::mat4 _object_matrix = transform.get_transform_matrix();

                ImGuizmo::Manipulate(
                    glm::value_ptr(m_engine->MainCamera.get_view_matrix()),
                    glm::value_ptr(m_engine->MainCamera.get_orthographic_projection_matrix()),
                    currentOperation,
                    ImGuizmo::WORLD,
                    glm::value_ptr(_object_matrix)
                );

                if (ImGuizmo::IsUsing())
                {
                    ImGuizmo::DecomposeMatrixToComponents(
                        glm::value_ptr(_object_matrix),
                        glm::value_ptr(transform.position),
                        glm::value_ptr(transform.rotation),
                        glm::value_ptr(transform.scale));
                }
            }

            m_engine->MainCamera.WindowSize.x = _scene_editor_window_width;
            m_engine->MainCamera.WindowSize.y = _scene_editor_window_height;
            m_engine->MainCamera.UpdateScreenSizeWithOrthographicSize(_scene_editor_window_width / _scene_editor_window_height);

            MELT::Input.MouseWindowPosition.x = ImGui::GetMousePos().x;
            MELT::Input.MouseWindowPosition.y = ImGui::GetMousePos().y;
            MELT::Input.MouseScreenPosition.x = ImVec2(MELT::Input.MouseWindowPosition.x - _cursor_screen_pos.x, MELT::Input.MouseWindowPosition.y - _cursor_screen_pos.y).x;
            MELT::Input.MouseScreenPosition.y = ImVec2(MELT::Input.MouseWindowPosition.x - _cursor_screen_pos.x, MELT::Input.MouseWindowPosition.y - _cursor_screen_pos.y).y;


            ImVec2 _screenPos     = ImVec2(MELT::Input.MouseWindowPosition.x - _cursor_screen_pos.x, MELT::Input.MouseWindowPosition.y - _cursor_screen_pos.y);
            ImVec2 _normalizedPos = RemapImVec2(_screenPos,
                                                0.0f, _scene_editor_window_width , 0.0f, 1.0f,
                                                0.0f, _scene_editor_window_height, 0.0f, 1.0f);

            ImVec2 _mouseWorldPos = RemapImVec2(_screenPos,
                                                0.0f, _scene_editor_window_width , -m_engine->MainCamera.HalfScreenWidth(),  m_engine->MainCamera.HalfScreenWidth(),
                                                0.0f, _scene_editor_window_height,  m_engine->MainCamera.HalfScreenHeight(), -m_engine->MainCamera.HalfScreenHeight());

            _mouseWorldPos.x += m_engine->MainCamera.Position.x;
            _mouseWorldPos.y += m_engine->MainCamera.Position.y;


            MELT::Input.MouseScreenNormalizedPosition.x = _normalizedPos.x;
            MELT::Input.MouseScreenNormalizedPosition.y = _normalizedPos.y;
            MELT::Input.MouseScreenWorldPosition.x      = _mouseWorldPos.x;
            MELT::Input.MouseScreenWorldPosition.y      = _mouseWorldPos.y;

            ImGui::Text("Window content          W H : (%.1f, %.1f)"     , _scene_editor_window_width                 , _scene_editor_window_height                );
            ImGui::Text("Orthographic projection W H : (%.1f, %.1f)"     , m_engine->MainCamera.ScreenSize.x            , m_engine->MainCamera.ScreenSize.y            );
            ImGui::Text("Mouse window position       : (%.1f, %.1f)"     , MELT::Input.MouseWindowPosition .x         , MELT::Input.MouseWindowPosition .y         );
            ImGui::Text("Mouse screen position       : (%.1f, %.1f)"     , MELT::Input.MouseScreenPosition.x          , MELT::Input.MouseScreenPosition.y          );
            ImGui::Text("Normalized position         : (%.1f, %.1f)"     , MELT::Input.MouseScreenNormalizedPosition.x, MELT::Input.MouseScreenNormalizedPosition.y);
            ImGui::Text("Mouse world position        : (%.1f, %.1f)"     , MELT::Input.MouseScreenWorldPosition.x     , MELT::Input.MouseScreenWorldPosition.y     );
            ImGui::InputFloat3("Camera position", glm::value_ptr(m_engine->MainCamera.Position));
            ImGui::SliderFloat("Near plane"       , &m_engine->MainCamera.near_plane, -100.0f, 0.0f);
            ImGui::SliderFloat("Far plane"        , &m_engine->MainCamera.far_plane ,     0.0, 1000.0f);
            ImGui::SliderFloat("Orthographic size", &m_engine->MainCamera.OrthographicSize, 1.0f, 200.f);


            auto _ent_view = _working_scene->ecs_registry.view<MELT::Transform, MELT::Light>();

            for (auto _entity : _ent_view)
            {
                auto& _transform = _ent_view.get<MELT::Transform>(_entity);

                M_VEC3 _world_pos = _transform.position;

                glm::mat4 _view           = m_engine->MainCamera.get_view_matrix();
                glm::mat4 _projection     = m_engine->MainCamera.get_orthographic_projection_matrix();
                glm::vec4 _clip_space_pos = _projection * _view * glm::vec4(_world_pos, 1.0f);

                glm::vec2 ndc = glm::vec2(_clip_space_pos.x, _clip_space_pos.y);
                glm::vec2 screenNormalized = ndc * 0.5f + 0.5f;

                glm::vec2 screenPos = glm::vec2(
                            screenNormalized.x  * _scene_editor_window_width  + _cursor_screen_pos.x,
                    (1.0f - screenNormalized.y) * _scene_editor_window_height + _cursor_screen_pos.y); // flip Y

                ImVec2 winPos = ImGui::GetWindowPos();
                ImVec2 winSize = ImGui::GetWindowSize();
                ImVec2 winMin = winPos;
                ImVec2 winMax = ImVec2(winPos.x + winSize.x, winPos.y + winSize.y);

                //Only draw if inside the window region
                if (screenPos.x >= winMin.x && screenPos.x <= winMax.x &&
                    screenPos.y >= winMin.y && screenPos.y <= winMax.y)
                {
                    ImVec2 boxSize = ImVec2(80.0f, 20.0f); // width x height
                    ImVec2 rectMin = ImVec2(screenPos.x - boxSize.x * 0.5f, screenPos.y - boxSize.y - 5.0f);
                    ImVec2 rectMax = ImVec2(screenPos.x + boxSize.x * 0.5f, screenPos.y - 5.0f);

                    // ImDrawList* drawList = ImGui::GetWindowDrawList();
                    // drawList->AddRectFilled(rectMin, rectMax, IM_COL32( 30, 144, 255, 220), 6.0f); // background
                    // drawList->AddRect      (rectMin, rectMax, IM_COL32(255, 255, 255, 255), 6.0f);      // border

                    ImVec2 textSize = ImGui::CalcTextSize("Label!");
                    ImVec2 textPos = ImVec2(
                        rectMin.x + (rectMax.x - rectMin.x - textSize.x) * 0.5f,
                        rectMin.y + (rectMax.y - rectMin.y - textSize.y) * 0.5f
                    );

                    //drawList->AddText(textPos, IM_COL32(255, 255, 255, 255), "Camera");

                    MELT::TextureData* _camera_icon = m_engine->manager_registry.get<MELT::ResourceManager>()->get_texture_data("camera_icon.png");
                    ImTextureID _camera_icon_id = (ImTextureID)(intptr_t)_camera_icon->p_texture->texture_id;

                    MELT::TextureData* _light_icon = m_engine->manager_registry.get<MELT::ResourceManager>()->get_texture_data("light_icon.png");
                    ImTextureID _light_icon_id = (ImTextureID)(intptr_t)_light_icon->p_texture->texture_id;

                    const ImVec2 size = ImVec2(32, 32);
                    ImVec2 drawMin = ImVec2(screenPos.x - size.x * 0.5f, screenPos.y - size.y);
                    ImVec2 drawMax = ImVec2(drawMin.x + size.x         , drawMin.y   + size.y);

                    // Step 5: Draw the texture
                    ImGui::GetWindowDrawList()->AddImage(_light_icon_id, drawMin, drawMax);
                }
            }

            // Push to bottom
            float padding = 10.0f; // Space from bottom edge
            float button_width = 120.0f;
            float button_height = 0.0f; // 0 = auto

            ImVec2 window_size = ImGui::GetWindowSize();
            ImVec2 cursor_pos = ImGui::GetCursorScreenPos();

            // Move to bottom center
            ImGui::SetCursorPosY(window_size.y - padding - ImGui::GetFrameHeight() * 4.0f); // Align bottom
            ImGui::SetCursorPosX((window_size.x - button_width) * 0.5f);             // Align center

            static int selected = 0;

            auto ToggleButton = [](const char* label, int index, int& selected, std::function<void()> onClick = nullptr, ImVec2 size = ImVec2(100, 30))
            {
                float roundness = 10.0f;

                ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, roundness);
                if (selected == index)
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.6f, 1.0f, 1.0f));
                else
                    ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyle().Colors[ImGuiCol_Button]);

                if (ImGui::Button(label, size)) {
                    selected = index;
                    if (onClick)
                        onClick(); // Call the function!
                }

                ImGui::PopStyleColor();
                ImGui::PopStyleVar();
            };

            ToggleButton("PLAY", 0, selected, [&]() {
                m_editor->application_mode_manager.change_state<GameplayMode>();
            });
            ImGui::SameLine();
            ToggleButton("PAUSE", 1, selected, [&]() {
                m_editor->application_mode_manager.change_state<EditorMode>();
            });
            ImGui::SameLine();
            ToggleButton("FORWARD", 2, selected, []() {
                printf("Right selected!\n");
            });
        }
        ImGui::End();
    }
}
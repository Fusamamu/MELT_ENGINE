#include "HierarchyGUI.h"
#include "MeltEngineEditor.h"

namespace MELT_EDITOR
{
    HierarchyGUI::HierarchyGUI()
    {

    }
    void HierarchyGUI::init(Editor* _editor)
    {
        m_editor = _editor;
        m_engine = _editor->engine;
    }

    void HierarchyGUI::draw_gui()
    {
        unsigned int ChildBackground_Color  = IM_COL32(26, 28, 27, 255);

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
                ImGui::Text("creation");
                ImGui::Separator();

                if (ImGui::BeginMenu("Create node"))
                {
                    ImGui::Text("Primitive");
                    ImGui::Separator();

                    if (ImGui::MenuItem("Cube node"))
                        m_engine->create_cube_node();

                    if (ImGui::MenuItem("Quad node"))
                    {
                    }

                    if (ImGui::MenuItem("Plane node"))
                        m_engine->create_plane_node();

                    ImGui::Separator();

                    if (ImGui::MenuItem("Camera node"))
                        m_engine->create_camera_node();
                    if (ImGui::MenuItem("Light node"))
                        m_engine->create_light_node();

                    ImGui::EndMenu();
                }

                if (ImGui::MenuItem("Create scene"))
                {
                }

                if (ImGui::BeginMenu("Create group"))
                {
                    if (ImGui::MenuItem("Empty group"))
                    {
                        // Create empty group logic
                    }

                    if (ImGui::MenuItem("Group with transform"))
                    {
                        // Create group with transform logic
                    }

                    ImGui::EndMenu();
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

            if (ImGui::CollapsingHeader("Scene 1"))
            {
                MELT::Scene* _working_scene = m_engine->manager_registry.get<MELT::SceneManager>()->working_scene;

                for(std::size_t _i = 0; _i < _working_scene->get_all_nodes().size(); ++_i)
                {
                    auto& _node = _working_scene->get_all_nodes()[_i];
                    if (_node.has_parent())
                        continue;
                    draw_node(_node);
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

    void HierarchyGUI::draw_node(MELT::Node& _node)
    {
        MELT::Scene* _working_scene = m_engine->manager_registry.get<MELT::SceneManager>()->working_scene;

        ImGuiTreeNodeFlags _flags = ImGuiTreeNodeFlags_OpenOnArrow;
        if (_node.is_selected)
            _flags |= ImGuiTreeNodeFlags_Selected;

        bool _opened = ImGui::TreeNodeEx(
            (void*)(uint64_t)(uint32_t)_node.get_entity(),
            _flags,
            "%s", _node.name.c_str());

        if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
        {
            _working_scene->deselect_all_nodes();
            _working_scene->selected_node_id = _node.id;
            _node.is_selected = true;
        }

        if (ImGui::BeginDragDropSource())
        {
            ImGui::SetDragDropPayload("NODE", &_node.id, sizeof(MELT::NodeID));
            ImGui::Text("Dragging %s", _node.name.c_str());
            ImGui::EndDragDropSource();
        }

        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* _payload = ImGui::AcceptDragDropPayload("NODE"))
            {
                MELT::NodeID _dropped_node = *(const MELT::NodeID*)_payload->Data;
                if (_dropped_node != _node.id)
                    _node.add_child(_dropped_node);
            }
            ImGui::EndDragDropTarget();
        }

        if (_opened)
        {
            for (auto _node_id : _node.get_children())
            {
                MELT::Node* _child_node = _working_scene->resolve_node_id(_node_id);
                draw_node(*_child_node);
            }
            ImGui::TreePop();
        }
    }
}
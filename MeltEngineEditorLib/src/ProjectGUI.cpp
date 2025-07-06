#include "MeltEngineEditor.h"
#include "ProjectGUI.h"

namespace MELT_EDITOR
{
    void ProjectGUI::init(Editor* _editor)
    {
        m_editor = _editor;
        m_engine = _editor->engine;

        MELT::TextureData* _folder_texture_data   = m_engine->manager_registry.get<MELT::ResourceManager>()->get_texture_data("open-file.png");
        MELT::TextureData* _material_texture_data = m_engine->manager_registry.get<MELT::ResourceManager>()->get_texture_data("material_icon.png");
        MELT::TextureData* _scene_texture_data    = m_engine->manager_registry.get<MELT::ResourceManager>()->get_texture_data("scene_icon.png");

        m_folder_icon_texture_id   = (ImTextureID)(intptr_t)_folder_texture_data  ->p_texture->texture_id;
        m_material_icon_texture_id = (ImTextureID)(intptr_t)_material_texture_data->p_texture->texture_id;
        m_scene_icon_texture_id    = (ImTextureID)(intptr_t)_scene_texture_data   ->p_texture->texture_id;
    }

    void ProjectGUI::draw_gui()
    {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ChildBackground_Color);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(4.0f, 4.0f));
        ImGui::Begin("Project");

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4.0f, 0));

        draw_tree_nodes();
        ImGui::SameLine();
        draw_selected_content();

        ImGui::PopStyleVar();

        ImGui::End();
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();
    }

    void ProjectGUI::draw_tree_nodes()
    {
        ImGui::BeginChild("Files", ImVec2(300, ImGui::GetContentRegionAvail().y), true);
        ImGui::BeginChild("##Scrollable List", ImVec2(0, ImGui::GetContentRegionAvail().y), true);
        if(std::filesystem::exists(m_editor->working_project_directory) && std::filesystem::is_directory(m_editor->working_project_directory))
            draw_file_browser(m_editor->working_project_directory);
        ImGui::EndChild();
        ImGui::EndChild();
    }

    void ProjectGUI::draw_selected_content()
    {
        ImGui::BeginChild("Child Window 2", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);

        if (!m_selected_directory.empty())
        {
            if (std::filesystem::is_directory(m_selected_directory))
            {
                for (const auto& _entry : std::filesystem::directory_iterator(m_selected_directory))
                {
                    std::string _path     = _entry.path().string();
                    std::string _filename = _entry.path().filename().string();
                    if (_filename == ".DS_Store")
                        continue;

                    if (_entry.path().extension() == ".yaml")
                    {
                        draw_icon(IconType::SCENE, _filename);
                        continue;
                    }

                    if (_entry.path().extension() == ".mat")
                    {
                        //draw_icon(IconType::MATERIAL, _filename);
                        draw_icon(IconType::MATERIAL, _entry);
                        continue;
                    }

                    draw_icon(IconType::FOLDER, _entry.path().filename().string());
                }
            }
        }

        ImGui::PushStyleColor(ImGuiCol_PopupBg, IM_COL32(73, 74, 70, 255));
        ImGui::PushStyleColor(ImGuiCol_Border , IM_COL32(73, 74, 70, 0));
        ImGui::PushStyleVar(ImGuiStyleVar_PopupRounding, 10.0f);
        if (ImGui::BeginPopupContextWindow("CC", ImGuiPopupFlags_MouseButtonRight))
        {
            if (ImGui::BeginMenu("Create"))
            {
                if (ImGui::MenuItem("Material"))
                {
                    if (std::filesystem::is_directory(m_selected_directory))
                    {
                        m_engine->Logger.log(m_selected_directory);

                        std::string _target_path = m_selected_directory + "/new_default_material.mat";
                        std::string _save_text   = MELT::GRAPHIC::create_material();

                        if (!std::filesystem::exists(_target_path))
                        {
                            std::ofstream _f_out(_target_path);
                            _f_out << _save_text.c_str();
                            _f_out.close();

                            m_engine->Logger.log("Created new YAML file");
                        } else {

                            std::ofstream _file;
                            _file.open(_target_path);
                            _file << _save_text.c_str();
                            _file.close();

                            m_engine->Logger.log("File already exists");
                        }
                    }
                }
                ImGui::EndMenu();
            }

            ImGui::EndPopup();
        }
        ImGui::PopStyleColor(2);
        ImGui::PopStyleVar();

        ImGui::EndChild();
    }

    void ProjectGUI::draw_icon(IconType _icon_type, const std::string& _label_name = "n/a")
    {
        ImTextureID _icon_texture_id;
        switch (_icon_type)
        {
            case IconType::FOLDER:
                _icon_texture_id = m_folder_icon_texture_id;
                break;
            case IconType::MATERIAL:
                _icon_texture_id = m_material_icon_texture_id;
                break;
            case IconType::SCENE:
                _icon_texture_id = m_scene_icon_texture_id;
                break;
        }

        ImGui::BeginGroup();
        ImGui::PushStyleColor(ImGuiCol_Button,        ChildBackground_Color); // normal
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ChildBackground_Color); // hover
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(0.1f, 0.4f, 0.7f, 1.0f));

        ImVec2 iconSize(m_icon_size, m_icon_size);

        if (ImGui::ImageButton(_icon_texture_id, iconSize))
        {
            m_editor->inspector_selection_context.type = InspectorSelectionType::MATERIAL;

            m_engine->Logger.log(_label_name);
        }
        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
        {
            m_engine->Logger.log("icon double click");
        }

        ImVec2 textSize = ImGui::CalcTextSize(_label_name.c_str());
        float textOffset = (iconSize.x - textSize.x) * 0.5f;
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + textOffset);
        ImGui::TextUnformatted(_label_name.c_str());

        ImGui::PopStyleColor(3);
        ImGui::EndGroup();
    }

    void ProjectGUI::draw_icon(IconType _icon_type, const std::filesystem::directory_entry& _entry)
    {
        std::string _target_path    = _entry.path().string();
        std::string _file_name      = _entry.path().filename().string();
        std::string _file_name_stem = _entry.path().stem().string();

        ImTextureID _icon_texture_id;
        switch (_icon_type)
        {
            case IconType::FOLDER:
                _icon_texture_id = m_folder_icon_texture_id;
            break;
            case IconType::MATERIAL:
                _icon_texture_id = m_material_icon_texture_id;
            break;
            case IconType::SCENE:
                _icon_texture_id = m_scene_icon_texture_id;
            break;
        }

        ImGui::BeginGroup();
        ImGui::PushStyleColor(ImGuiCol_Button,        ChildBackground_Color); // normal
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ChildBackground_Color); // hover
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(0.1f, 0.4f, 0.7f, 1.0f));

        ImVec2 iconSize(m_icon_size, m_icon_size);

        if (ImGui::ImageButton(_icon_texture_id, iconSize))
        {
            m_editor->inspector_selection_context.type          = InspectorSelectionType::MATERIAL;
            m_editor->inspector_selection_context.selected_uuid = "";

            MELT::GRAPHIC::Material* _material = MELT::AssetRegistry::instance().get_by_name<MELT::GRAPHIC::Material>(_file_name_stem);
            if (_material != nullptr)
                m_engine->manager_registry.get<MELT::RenderPipeline>()->shader_preview.set_preview_target_material(_material);
        }
        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
        {
            m_engine->Logger.log("icon double click");
        }

        ImVec2 textSize = ImGui::CalcTextSize(_file_name.c_str());
        float textOffset = (iconSize.x - textSize.x) * 0.5f;
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + textOffset);
        ImGui::TextUnformatted(_file_name.c_str());

        ImGui::PopStyleColor(3);
        ImGui::EndGroup();
    }

    void ProjectGUI::draw_file_browser(const std::filesystem::path& _file_path)
    {
        for (const auto& entry : std::filesystem::directory_iterator(_file_path)) {

            std::string _path     = entry.path().string();
            std::string _filename = entry.path().filename().string();

            if (_filename == ".DS_Store")
                continue;

            if (entry.is_regular_file())
            {
                if (ImGui::Selectable(_filename.c_str()))
                {
                    std::string selectedFile = entry.path().string();
                }
            }
            else if (entry.is_directory())
            {
                int _flag = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
                if (m_selected_directory == _path)
                    _flag |= ImGuiTreeNodeFlags_Selected;

                bool isOpen    = ImGui::TreeNodeEx(_filename.c_str(), _flag);
                bool isHovered = ImGui::IsItemHovered();
                bool isClicked = ImGui::IsItemClicked();

                if (!isOpen && isHovered && isClicked)
                {
                    m_selected_directory = _path;
                }

                if (isOpen)
                {
                    draw_file_browser(entry.path());
                    ImGui::TreePop();
                }
            }
        }
    }
}
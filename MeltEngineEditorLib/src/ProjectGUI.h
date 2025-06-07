#ifndef PROJECTGUI_H
#define PROJECTGUI_H

#include "EditorCore.h"

namespace MELT_EDITOR
{
    class Editor;

    enum class IconType
    {
        FOLDER = 0,
        MATERIAL,
        SCENE,
    };

    class ProjectGUI
    {
    public:
        bool is_open;
        ProjectGUI()  = default;
        ~ProjectGUI() = default;
        void init(Editor* _editor);
        void draw_gui();
    private:
        Editor*       m_editor;
        MELT::Engine* m_engine;

        float m_icon_size = 64.0f;

        ImTextureID m_folder_icon_texture_id;
        ImTextureID m_material_icon_texture_id;
        ImTextureID m_scene_icon_texture_id;

        std::string m_selected_directory;

        unsigned int WindowBackground_Color = IM_COL32(33, 36, 35, 255);
        unsigned int ChildBackground_Color  = IM_COL32(26, 28, 27, 255);

        void draw_tree_nodes();
        void draw_selected_content();
        void draw_icon(IconType _icon_type, const std::string& _label_name);
        void draw_file_browser(const std::filesystem::path& _file_path);
    };
}

#endif

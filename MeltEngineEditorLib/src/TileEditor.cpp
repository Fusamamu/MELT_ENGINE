#include "TileEditor.h"
#include "MeltEngineEditor.h"

namespace MELT_EDITOR
{
    TileEditor::TileEditor()
    {

    }

    void TileEditor::init(Editor* _editor)
    {
        m_editor = _editor;
        m_engine = _editor->engine;
    }

    void TileEditor::draw_gui()
    {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(26, 28, 27, 255));
        if (ImGui::Begin("Tile Editor"))
        {
            ImGui::InputInt("Column", &column);
            ImGui::InputInt("Row"   , &row);

            if (ImGui::Button("Generate grid"))
            {
                std::shared_ptr<MELT::ResourceManager> _resource_manager = m_engine->manager_registry.get<MELT::ResourceManager>();
                std::shared_ptr<MELT::SceneManager>    _scene_manager    = m_engine->manager_registry.get<MELT::SceneManager>();

                for (std::size_t _i = 0; _i < column; ++_i)
                {
                    for (std::size_t _j = 0; _j < row; ++_j)
                    {
                        MELT::Node& _node = _scene_manager->working_scene->create_node("Entity");
                        _node.add_component<MELT::Transform>();
                        _node.add_component<MELT::MeshRenderer>();
                        _node.add_component<MELT::BoxCollider>();
                        _node.add_component<MELT::NodeEditor>();

                        MELT::Transform& _transform = _node.get_component<MELT::Transform>();

                        _transform.position.x += _i * 1.5f;
                        _transform.position.z += _j * 1.5f;

                        MELT::MeshRenderer& _mesh_renderer = _node.get_component<MELT::MeshRenderer>();
                        _mesh_renderer.set_mesh_data(&_resource_manager->default_cube);
                        _mesh_renderer.set_buffer_data();

                        MELT::NodeEditor& _node_editor = _node.get_component<MELT::NodeEditor>();
                        _node_editor.id = _node.id;

                        tile_ids.push_back(_node.id);
                    }
                }
            }

            if (ImGui::Button("Generate nodes"))
            {
                std::shared_ptr<MELT::ResourceManager> _resource_manager = m_engine->manager_registry.get<MELT::ResourceManager>();
                std::shared_ptr<MELT::SceneManager>    _scene_manager    = m_engine->manager_registry.get<MELT::SceneManager>();

                for (std::size_t _i = 0; _i < column; ++_i)
                {
                    for (std::size_t _j = 0; _j < row; ++_j)
                    {
                        std::string node_name = "Tile node " + std::to_string(_i) + "," + std::to_string(_j);

                        MELT::Node& _node = _scene_manager->working_scene->create_node(node_name);
                        _node.add_component<MELT::Transform>();
                        _node.add_component<MELT::MeshRenderer>();
                        _node.add_component<MELT::NodeEditor>();

                        MELT::Transform& _transform = _node.get_component<MELT::Transform>();

                        _transform.position.x += _i * 1.5f;
                        _transform.position.z += _j * 1.5f;
                        _transform.scale = M_VEC3(0.25f, 0.25f, 0.25f);

                        MELT::MeshRenderer& _mesh_renderer = _node.get_component<MELT::MeshRenderer>();
                        _mesh_renderer.set_mesh_data(_resource_manager->get_mesh_data("Sphere"));
                        _mesh_renderer.set_buffer_data();

                        MELT::NodeEditor& _node_editor = _node.get_component<MELT::NodeEditor>();
                        _node_editor.id = _node.id;

                        tile_ids.push_back(_node.id);
                    }
                }
            }

            if (ImGui::Button("Clear"))
            {
                m_engine->deselect_all_nodes();
                std::shared_ptr<MELT::SceneManager> _scene_manager = m_engine->manager_registry.get<MELT::SceneManager>();
                for (const MELT::NodeID& _id : tile_ids)
                    _scene_manager->working_scene->destroy_node_by_id(_id);
                tile_ids.clear();
            }
        }
        ImGui::End();
        ImGui::PopStyleColor();
    }
}

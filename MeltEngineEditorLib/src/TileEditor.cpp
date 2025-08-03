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
        TileEditorMode& _tile_editor_mode = m_editor->application_mode_manager.get_state<TileEditorMode>();

        ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(26, 28, 27, 255));
        if (ImGui::Begin("Tile Editor"))
        {
            ImGui::PushStyleColor(ImGuiCol_Button, use_edit_mode ? ImVec4(0.2f, 0.7f, 0.2f, 1.0f) : ImVec4(0.7f, 0.2f, 0.2f, 1.0f));
            if (ImGui::Button(use_edit_mode ? "EDIT ON" : "EDIT OFF"))
            {
                use_edit_mode = !use_edit_mode;
                if (use_edit_mode)
                {
                    m_engine->manager_registry.get<MELT::RenderPipeline>()->clear_color = glm::vec4(0.30f, 0.34f, 0.36f, 1.0f);
                    m_editor->application_mode_manager.change_state<TileEditorMode>();
                }
                else
                {
                    m_engine->manager_registry.get<MELT::RenderPipeline>()->clear_color = glm::vec4(222.0f/255.0f, 217.0f/255.0f, 226.0f/255.0f, 33.0f/255.0f);
                    m_editor->application_mode_manager.change_state<EditorMode>();
                }
            }
            ImGui::PopStyleColor();

            for (int i = 0; i < 3; ++i) {
                if (i > 0)
                    ImGui::SameLine();

                if (i == current_selection)
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.6f, 0.9f, 1.0f)); // Active
                else
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.3f, 0.3f, 1.0f)); // Inactive

                if (ImGui::Button(m_options[i]))
                    current_selection = i;

                ImGui::PopStyleColor();
            }


            ImGui::InputInt("Column" , &column);
            ImGui::InputInt("Row"    , &row);
            ImGui::InputInt("Height" , &height);

            if (ImGui::Button("Generate grid"))
            {
                std::shared_ptr<MELT::ResourceManager> _resource_manager = m_engine->manager_registry.get<MELT::ResourceManager>();
                std::shared_ptr<MELT::SceneManager>    _scene_manager    = m_engine->manager_registry.get<MELT::SceneManager>();

                MELT::Scene* _working_scene = _scene_manager->working_scene;

                auto& _ctx = _working_scene->ecs_registry.ctx();
                if (_ctx.contains<MELT::BlockTileGrid>())
                    _ctx.erase<MELT::BlockTileGrid>();

                _ctx.emplace<MELT::BlockTileGrid>(MELT::BlockTileGrid{MELT::Grid(column, 1, row)});

                auto& _block_tile = _ctx.get<MELT::BlockTileGrid>();

                for (std::size_t _i = 0; _i < column; ++_i)
                {
                    for (std::size_t _j = 0; _j < row; ++_j)
                    {
                        MELT::Node& _node = _scene_manager->working_scene->create_node("Entity");
                        _node.add_component<MELT::Transform   >();
                        _node.add_component<MELT::MeshRenderer>();
                        _node.add_component<MELT::BoxCollider >();
                        _node.add_component<MELT::Tile        >();
                        _node.add_component<MELT::NodeEditor  >();

                        MELT::Transform& _transform = _node.get_component<MELT::Transform>();

                        _transform.position.x += _i + 0.5f;
                        _transform.position.z += _j + 0.5f;

                        MELT::MeshRenderer& _mesh_renderer = _node.get_component<MELT::MeshRenderer>();
                        _mesh_renderer.set_mesh_data(&_resource_manager->default_cube);
                        _mesh_renderer.set_buffer_data();
                        _mesh_renderer.set_material_by_uuid(MELT::AssetRegistry::instance().get_meta_by_name<MELT::GRAPHIC::Material>("new_default_material").uuid, true);

                        MELT::NodeEditor& _node_editor = _node.get_component<MELT::NodeEditor>();
                        _node_editor.id = _node.id;

                        MELT::Tile& _tile = _node.get_component<MELT::Tile>();
                        _tile.idx = _i;
                        _tile.idy = 0;
                        _tile.idz = _j;

                        //Will remove this
                        tile_ids.push_back(_node.id);//need to remove this


                        _block_tile.grid.add_node_at(_node.get_entity(), _i, 0, _j);
                    }
                }
            }

            if (ImGui::Button("Generate nodes"))
            {
                std::shared_ptr<MELT::ResourceManager> _resource_manager = m_engine->manager_registry.get<MELT::ResourceManager>();
                std::shared_ptr<MELT::SceneManager>    _scene_manager    = m_engine->manager_registry.get<MELT::SceneManager>();

                MELT::Scene* _working_scene = _scene_manager->working_scene;

                auto& _ctx = _working_scene->ecs_registry.ctx();
                if (_ctx.contains<MELT::VolumeNodeGrid>())
                    _ctx.erase<MELT::VolumeNodeGrid>();

                _ctx.emplace<MELT::VolumeNodeGrid>(MELT::VolumeNodeGrid{MELT::Grid(column + 1, height + 1, row + 1)});

                auto& _volume_node = _ctx.get<MELT::VolumeNodeGrid>();

                for (std::size_t _i = 0; _i < column + 1; ++_i)
                {
                    for (std::size_t _j = 0; _j < row + 1; ++_j)
                    {
                        for (std::size_t _k = 0; _k < height + 1; ++_k)
                        {
                            std::string node_name = "Tile node " + std::to_string(_i) + "," + std::to_string(_j);

                            MELT::Node& _node = _scene_manager->working_scene->create_node(node_name);
                            _node.add_component<MELT::Transform>();
                            _node.add_component<MELT::MeshRenderer>();
                            _node.add_component<MELT::NodeEditor>();
                            _node.add_component<MELT::VolumePoint>();

                            MELT::Transform& _transform = _node.get_component<MELT::Transform>();

                            _transform.position.x += _i;
                            _transform.position.y += _k - 0.5f;
                            _transform.position.z += _j;
                            _transform.scale = M_VEC3(0.25f, 0.25f, 0.25f);

                            MELT::MeshRenderer& _mesh_renderer = _node.get_component<MELT::MeshRenderer>();
                            _mesh_renderer.set_mesh_data(_resource_manager->get_mesh_data("Sphere"));
                            _mesh_renderer.set_buffer_data();
                            _mesh_renderer.set_material_by_uuid(MELT::AssetRegistry::instance().get_meta_by_name<MELT::GRAPHIC::Material>("new_default_material").uuid, true);

                            MELT::NodeEditor& _node_editor = _node.get_component<MELT::NodeEditor>();
                            _node_editor.id = _node.id;

                            MELT::VolumePoint& _volume_point = _node.get_component<MELT::VolumePoint>();
                            _volume_point.idx = _i;
                            _volume_point.idy = _k;
                            _volume_point.idz = _j;

                            tile_ids.push_back(_node.id);//will remove this

                            _volume_node.grid.at(_i, _k, _j) = _node.get_entity();
                        }
                    }
                }
            }

            if (ImGui::Button("Connect references"))
            {
                std::shared_ptr<MELT::SceneManager> _scene_manager = m_engine->manager_registry.get<MELT::SceneManager>();
                MELT::Scene* _working_scene = _scene_manager->working_scene;

                auto& _ctx = _working_scene->ecs_registry.ctx();
                if (!_ctx.contains<MELT::BlockTileGrid>())
                    return;
                if (!_ctx.contains<MELT::VolumeNodeGrid>())
                    return;

                auto& _tile_block  = _ctx.get<MELT::BlockTileGrid >();
                auto& _volume_node = _ctx.get<MELT::VolumeNodeGrid>();

                for (std::size_t _i = 0; _i < _tile_block.grid.width; ++_i)
                {
                    for (std::size_t _j = 0; _j < _tile_block.grid.depth; ++_j)
                    {
                        auto& _tile = _working_scene->ecs_registry.get<MELT::Tile>(_tile_block.grid.at(_i, 0, _j));

                        _tile.volume_point_refs[0] = _volume_node.grid.at(_i, 0, _j);
                        _tile.volume_point_refs[1] = _volume_node.grid.at(_i, 0, _j);
                        _tile.volume_point_refs[2] = _volume_node.grid.at(_i, 0, _j);
                        _tile.volume_point_refs[3] = _volume_node.grid.at(_i, 0, _j);

                        _tile.volume_point_refs[4] = _volume_node.grid.at(_i, 0, _j);
                        _tile.volume_point_refs[5] = _volume_node.grid.at(_i, 0, _j);
                        _tile.volume_point_refs[6] = _volume_node.grid.at(_i, 0, _j);
                        _tile.volume_point_refs[7] = _volume_node.grid.at(_i, 0, _j);
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

                MELT::Scene* _working_scene = _scene_manager->working_scene;
                auto& _ctx = _working_scene->ecs_registry.ctx();

                if (_ctx.contains<MELT::BlockTileGrid>())
                    _ctx.erase<MELT::BlockTileGrid>();
                if (_ctx.contains<MELT::VolumeNodeGrid>())
                    _ctx.erase<MELT::VolumeNodeGrid>();
            }
        }
        ImGui::End();
        ImGui::PopStyleColor();
    }
}

#ifndef GRID_H
#define GRID_H

#include "Core.h"
#include "Node.h"
#include "Components.h"

namespace MELT
{
    class Grid
    {
    public:
        using NodeIdx = int32_t;
        using Node    = entt::entity;

        size_t width, height, depth;

        Grid(size_t w, size_t h, size_t d)
            : width(w), height(h), depth(d), m_data(w * h * d)
        {
            for (entt::entity& _e : m_data)
                _e = entt::null;
        }

        ~Grid() = default;

        void init()
        {
        }

        [[nodiscard]] bool is_valid_at(NodeIdx x, NodeIdx y, NodeIdx z) const;

        [[nodiscard]] const Grid::Node& at(size_t x, size_t y, size_t z) const { return m_data[index(x, y, z)]; }
                            Grid::Node& at(size_t x, size_t y, size_t z)       { return m_data[index(x, y, z)]; }

        void add_node_at    (const Grid::Node& _node, NodeIdx _x, NodeIdx _y, NodeIdx _z);
        void add_node_on_top(const Grid::Node& _node, NodeIdx _x, NodeIdx _y, NodeIdx _z);
        void remove_node_at (const Grid::Node& _node, NodeIdx _x, NodeIdx _y, NodeIdx _z);

    private:
        std::vector<Grid::Node> m_data;

        [[nodiscard]] size_t index(size_t _x, size_t _y, size_t _z) const;
    };

    class GridNodeBuilder
    {
        Grid::Node build(MELT::Node& _node, M_VEC3 _at_position, M_VEC3_I _at_index)
        {
            auto& _transform     = _node.add_component<MELT::Transform   >();
            auto& _mesh_renderer = _node.add_component<MELT::MeshRenderer>();
            auto& _box_collider  = _node.add_component<MELT::BoxCollider >();
            auto& _tile          = _node.add_component<MELT::Tile        >();
            auto& _node_editor   = _node.add_component<MELT::NodeEditor  >();

            _node_editor.id = _node.id;
            _transform.set_position(_at_position);
            _tile     .set_idx     (_at_index   );

            // const AssetMetadata& _a = AssetRegistry::instance().get_meta_by_name<Mesh>("default_cube");
            // auto _uuid = _a.uuid;
            // Mesh* _mesh = AssetRegistry::instance().get<Mesh>(_uuid);
            //
            //
            // _mesh_renderer.set_mesh       (_mesh);
            // _mesh_renderer.set_buffer_data(_mesh);


            _mesh_renderer.set_material_by_uuid(AssetRegistry::instance().get_meta_by_name<GRAPHIC::Material>("new_default_material").uuid, true);
        }
    };

    struct BlockTileGrid{
        Grid grid;
    };

    struct VolumeNodeGrid{
        Grid grid;
    };
}

#endif

#include "Grid.h"
#include "Scene.h"

namespace MELT
{
    [[nodiscard]] size_t Grid::index(size_t _x, size_t _y, size_t _z) const
    {
        if (_x >= width || _y >= height || _z >= depth)
            throw std::out_of_range("TileGrid::index out of range");

        return _x + _y * width + _z * width * height;
    }

    [[nodiscard]] bool Grid::is_valid_at(NodeIdx x, NodeIdx y, NodeIdx z) const {
        return x >= 0 && x < static_cast<NodeIdx>(width ) &&
               y >= 0 && y < static_cast<NodeIdx>(height) &&
               z >= 0 && z < static_cast<NodeIdx>(depth );
    }

    void Grid::build_default(MELT::SceneNode& _node, M_VEC3 _at_position, M_VEC3_I _at_index)
    {
        auto& _transform     = _node.add_component<MELT::Transform   >();
        auto& _mesh_renderer = _node.add_component<MELT::MeshRenderer>();
        auto& _box_collider  = _node.add_component<MELT::BoxCollider >();
        auto& _tile          = _node.add_component<MELT::Tile        >();
        auto& _node_editor   = _node.add_component<MELT::NodeEditor  >();

        _node_editor.id = _node.id;
        _transform.set_position(_at_position);
        _tile     .set_idx     (_at_index   );

        _mesh_renderer.load_mesh_handle    (AssetRegistry::instance().get_handle_by_name<Mesh>             ("default_cube"        ));
        _mesh_renderer.load_material_handle(AssetRegistry::instance().get_handle_by_name<GRAPHIC::Material>("new_default_material"));
    }

    void Grid::add_node_at(const Grid::Node& _node, NodeIdx _x, NodeIdx _y, NodeIdx _z)
    {
        if (!is_valid_at(_x, _y, _z))
            return;
        m_data[index(_x, _y, _z)] = _node.id;
    }

    void Grid::add_node_on_top(const Grid::Node& _node, NodeIdx _x, NodeIdx _y, NodeIdx _z)
    {
        if (!is_valid_at(_x, _y + 1, _z))
            return;
        m_data[index(_x, _y + 1, _z)] = _node.id;
    }

    void Grid::remove_node_at(const Grid::Node& _node, NodeIdx _x, NodeIdx _y, NodeIdx _z)
    {
        if (!is_valid_at(_x, _y, _z))
            return;
        //m_data[index(_x, _y, _z)] = entt::null;
    }

    void Grid::clear_all_from(Scene* _scene)
    {
        for (NodeID& _node_id : m_data)
            _scene->destroy_node_by_id(_node_id);
        m_data.clear();
    }
}

#include "Grid.h"

#include <Transform.h>

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

    void Grid::add_node_at(const Grid::Node& _node, NodeIdx _x, NodeIdx _y, NodeIdx _z)
    {
        if (!is_valid_at(_x, _y, _z))
            return;
        m_data[index(_x, _y, _z)] = _node;
    }

    void Grid::add_node_on_top(const Grid::Node& _node, NodeIdx _x, NodeIdx _y, NodeIdx _z)
    {
        if (!is_valid_at(_x, _y + 1, _z))
            return;
        m_data[index(_x, _y + 1, _z)] = _node;
    }

    void Grid::remove_node_at(const Grid::Node& _node, NodeIdx _x, NodeIdx _y, NodeIdx _z)
    {
        if (!is_valid_at(_x, _y, _z))
            return;
        m_data[index(_x, _y, _z)] = entt::null;
    }
}

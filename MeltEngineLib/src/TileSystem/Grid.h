#ifndef GRID_H
#define GRID_H

#include "Core.h"
#include "Node.h"
#include "Components.h"

namespace MELT
{
    class Scene;

    class Grid
    {
    public:
        using NodeIdx = int32_t;
        using Node    = MELT::SceneNode;

        size_t width, height, depth;

        Grid(size_t w, size_t h, size_t d)
            : width(w), height(h), depth(d), m_data(w * h * d)
        {

        }

        Grid() = default;
        ~Grid() = default;

        void init()
        {
        }

        [[nodiscard]] bool is_valid_at(NodeIdx x, NodeIdx y, NodeIdx z) const;

        [[nodiscard]] const NodeID& at(size_t x, size_t y, size_t z) const { return m_data[index(x, y, z)]; }
                            NodeID& at(size_t x, size_t y, size_t z)       { return m_data[index(x, y, z)]; }

        void add_node_at    (const Grid::Node& _node, NodeIdx _x, NodeIdx _y, NodeIdx _z);
        void add_node_on_top(const Grid::Node& _node, NodeIdx _x, NodeIdx _y, NodeIdx _z);
        void remove_node_at (const Grid::Node& _node, NodeIdx _x, NodeIdx _y, NodeIdx _z);

        void build_default(MELT::SceneNode& _node, M_VEC3 _at_position, M_VEC3_I _at_index);

        void clear_all_from(Scene* _scene);

    private:
        std::vector<NodeID> m_data;

        [[nodiscard]] size_t index(size_t _x, size_t _y, size_t _z) const;
    };

    struct BlockTileGrid{
        Grid grid;
    };

    struct VolumeNodeGrid{
        Grid grid;
    };
}

#endif

#include "TileGridFixedSize.h"

namespace MELT
{
    inline float heuristic(int x1, int y1, int x2, int y2)
    {
        return static_cast<float>(std::abs(x1 - x2) + std::abs(y1 - y2)); // Manhattan
    }

    std::vector<TileNode> find_path(entt::registry& _registry, Grid& _grid, int start_x, int start_y, int end_x, int end_y, int z_layer)
    {
        auto compare = [](const TileNode* a, const TileNode* b) {
            return a->f_cost() > b->f_cost();
        };

        std::priority_queue<TileNode*, std::vector<TileNode*>, decltype(compare)> open(compare);

        //std::unordered_map<std::pair<int, int>, TileNode, NodeHash> all_nodes;

        // auto get_node = [&](int x, int y) -> TileNode&
        // {
        //     auto key = std::make_pair(x, y);
        //     if (all_nodes.find(key) == all_nodes.end())
        //         all_nodes[key] = TileNode{x, y};
        //     return all_nodes[key];
        // };
        //
        // TileNode& start_node = get_node(start_x, start_y);
        // start_node.g_cost = 0;
        // start_node.h_cost = heuristic(start_x, start_y, end_x, end_y);
        //
        // open.push(&start_node);
        //
        // std::unordered_set<std::pair<int, int>, NodeHash> closed;
        //
        // const std::array<std::pair<int, int>, 4> directions =
        // {
        //     {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}
        // };
        //
        // while (!open.empty()) {
        //     TileNode* current = open.top();
        //     open.pop();
        //
        //     if (current->x == end_x && current->y == end_y) {
        //         // Reconstruct path
        //         std::vector<TileNode> path;
        //         while (current) {
        //             path.push_back(*current);
        //             current = current->parent;
        //         }
        //         std::reverse(path.begin(), path.end());
        //         return path;
        //     }
        //
        //     closed.insert({current->x, current->y});
        //
        //     for (auto [dx, dy] : directions) {
        //         int nx = current->x + dx;
        //         int ny = current->y + dy;
        //
        //         if (!_grid.is_valid_at(nx, ny, z_layer))
        //             continue;
        //
        //         entt::entity tile_entity = _grid.at(nx, ny, z_layer);
        //         if (tile_entity == entt::null || !_registry.valid(tile_entity))
        //             continue;
        //
        //         const Tile& tile = _registry.get<Tile>(tile_entity);
        //         if (!tile.walkable)
        //             continue;
        //
        //         // if (closed.contains({nx, ny}))
        //         //     continue;
        //
        //         TileNode& neighbor = get_node(nx, ny);
        //
        //         float tentative_g = current->g_cost + 1.0f;
        //
        //         if (neighbor.parent == nullptr || tentative_g < neighbor.g_cost) {
        //             neighbor.parent = current;
        //             neighbor.g_cost = tentative_g;
        //             neighbor.h_cost = heuristic(nx, ny, end_x, end_y);
        //             open.push(&neighbor);
        //         }
        //     }
        // }
         return {}; // No path found
    }
}

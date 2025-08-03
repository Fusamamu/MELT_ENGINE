#ifndef TILE_GRID_H
#define TILE_GRID_H

namespace MELT
{
    enum class TileType
    {
        NONE
    };

    struct Tile
    {
        bool walkable = true;

        TileType type;
        M_VEC3 position;

        uint32_t idx, idy, idz;
        std::array<entt::entity, 8> volume_point_refs; // -ZX, -Z-X

        void set_idx(M_VEC3_I _index)
        {
            idx = _index.x;
            idy = _index.y;
            idz = _index.z;
        }
    };

    struct VolumePoint
    {
        uint32_t idx, idy, idz;
        std::array<entt::entity, 8> tile_refs;
        VolumePoint() = default;
    };

    template<size_t W, size_t H, size_t D>
    class TileGridFixedSize
    {
    public:
        size_t width, height, depth;

        TileGridFixedSize(): width(W), height(H), depth(D) {}
        ~TileGridFixedSize() = default;

        void init()
        {
            
        }

        bool is_valid_at(int32_t _idx, int32_t _idy, int32_t _idz)
        {
            if (_idx < 0 || _idx >= width)
                return false;
            if (_idy < 0 || _idy >= height)
                return false;
            if (_idz < 0 || _idz >= depth)
                return false;
            return true;
        }

        Tile& at(size_t _idx, size_t _idy, size_t _idz){
            return m_data[_idx][_idy][_idz];
        }

        [[nodiscard]] const Tile& at(size_t _idx, size_t _idy, size_t _idz) const{
            return m_data[_idx][_idy][_idz];
        }
    private:
        Tile m_data[W][H][D] = { };
    };


    struct TileNode
    {
        int x, y;

        float g_cost = 0.0f;
        float h_cost = 0.0f;
        float f_cost() const { return g_cost + h_cost; }

        TileNode* parent = nullptr;

        bool operator==(const TileNode& other) const {
            return x == other.x && y == other.y;
        }
    };

    struct NodeHash {
        std::size_t operator()(const TileNode& n) const noexcept {
            std::size_t h1 = std::hash<int>()(n.x);
            std::size_t h2 = std::hash<int>()(n.y);
            return h1 ^ (h2 << 1); // simple but works for small grids
        }
    };

    inline float heuristic(int x1, int y1, int x2, int y2);
    // std::vector<TileNode> find_path(entt::registry& _registry, Grid& _grid, int start_x, int start_y, int end_x, int end_y, int z_layer = 0);
}

#endif

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
        TileType type;
        uint32_t idx, idy, idz;
        M_VEC3 position;
        bool walkable = true;
    };

    struct VolumePoint
    {
        uint32_t idx, idy, idz;
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

    class Grid
    {
    public:
        size_t width, height, depth;

        Grid(size_t w, size_t h, size_t d)
            : width(w), height(h), depth(d), m_data(w * h * d)
        {

        }

        ~Grid() = default;

        void init()
        {
        }

        [[nodiscard]] bool is_valid_at(int32_t x, int32_t y, int32_t z) const {
            return x >= 0 && x < static_cast<int32_t>(width) &&
                   y >= 0 && y < static_cast<int32_t>(height) &&
                   z >= 0 && z < static_cast<int32_t>(depth);
        }

        entt::entity& at(size_t x, size_t y, size_t z) {
            return m_data[index(x, y, z)];
        }

        [[nodiscard]] const entt::entity& at(size_t x, size_t y, size_t z) const {
            return m_data[index(x, y, z)];
        }

    private:
        std::vector<entt::entity> m_data;

        [[nodiscard]] size_t index(size_t x, size_t y, size_t z) const {
            if (x >= width || y >= height || z >= depth)
                throw std::out_of_range("TileGrid::index out of range");
            return x + y * width + z * width * height;
        }
    };

    struct BlockTileGrid{
        Grid grid;
    };

    struct VolumeNodeGrid{
        Grid grid;
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
    std::vector<TileNode> find_path(entt::registry& _registry, Grid& _grid, int start_x, int start_y, int end_x, int end_y, int z_layer = 0);
}

#endif

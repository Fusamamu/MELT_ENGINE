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
    };

    template<size_t W, size_t H, size_t D>
    class TileGrid
    {
    public:
        size_t width, height, depth;

        TileGrid(): width(W), height(H), depth(D) {}
        ~TileGrid() = default;

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
}

#endif

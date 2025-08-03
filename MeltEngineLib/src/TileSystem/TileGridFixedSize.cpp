#include "TileGridFixedSize.h"

namespace MELT
{
    inline float heuristic(int x1, int y1, int x2, int y2)
    {
        return static_cast<float>(std::abs(x1 - x2) + std::abs(y1 - y2)); // Manhattan
    }
}

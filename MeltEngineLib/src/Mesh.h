#pragma once
#include "Core.h"
#include "Vertex.h"

namespace MELT
{
    struct Mesh
    {
        std::vector<Vertex_1P1C1T1N> Vertices;
        std::vector<unsigned int> Indices;
    };
}
#pragma once
#include "Core.h"
#include "Vertex.h"


namespace MELT
{
    struct Mesh
    {
        std::vector<Vertex_1P1C1T1N> vertices;
        std::vector<unsigned int> indices;

        [[nodiscard]] std::size_t get_vertices_size() const
        {
            return vertices.size() * sizeof(Vertex_1P1C1T1N);
        }
        [[nodiscard]] std::size_t get_indices_size () const
        {
            return indices.size() * sizeof(unsigned int);
        }
    };

    struct MeshData
    {
        std::string name;
        UUID uuid;
        Mesh* mesh;

        MeshData():
            name(""),
            mesh(nullptr)
        {
            uuid = GenerateUUID(reinterpret_cast<uintptr_t>(this));
        }
    };
}
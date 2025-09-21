#pragma once
#include "Core.h"
#include "Vertex.h"

namespace MELT
{
    struct Mesh
    {
        std::vector<uint8_t> vertex_buffer;
        std::vector<unsigned int> index_buffer;

        VertexLayout layout;

        [[nodiscard]] std::size_t get_vertex_buffer_size() const { return vertex_buffer.size(); }
        [[nodiscard]] std::size_t get_index_buffer_size () const { return index_buffer .size() * sizeof(unsigned int); }

        UUID gen_uuid() const {
            return generate_uuid(reinterpret_cast<uintptr_t>(this));
        }
    };

    //Will remove this
    struct MeshData
    {
        UUID uuid;
        std::string name;

        Mesh* mesh;

        MeshData():
            name(""),
            mesh(nullptr)
        {
            uuid = generate_uuid(reinterpret_cast<uintptr_t>(this));
        }
    };
}
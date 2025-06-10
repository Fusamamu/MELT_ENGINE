#pragma once
#include "Core.h"

namespace MELT
{
    enum class VertexAttribute
    {
        POSITION,
        NORMAL,
        TEXCOORD_0,
        COLOR,
        TANGENT
    };

    struct VertexElement {
        VertexAttribute attribute;
        uint32_t offset;    // offset in bytes in the vertex struct
        uint32_t size;      // size in bytes of attribute (e.g. 12 for vec3 float)
        GLenum glType;      // GL_FLOAT, GL_UNSIGNED_BYTE etc.
        int components;     // number of components (e.g. 3 for vec3)
        bool normalized;    // normalized flag for GL
    };

    struct VertexLayout
    {
        std::vector<VertexElement> elements;

        uint32_t stride;

        void addElement(VertexAttribute _attr, uint32_t _offset, uint32_t _size, GLenum _glType, int _components, bool _normalized = false)
        {
            elements.push_back({ _attr, _offset, _size, _glType, _components, _normalized });
        }
    };

    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 color;
        glm::vec2 texCoord;

        Vertex();
        ~Vertex();
    };

    struct Vertex_PCTN
    {
        glm::vec3 position;
        glm::vec3 color;
        glm::vec2 texCoord;
        glm::vec3 normal;

        Vertex_PCTN(){ }
        ~Vertex_PCTN(){ }
    };

    struct Vertex_P
    {
        float x, y, z;
    };

    struct Vertex_PN
    {
        float x, y, z;
        float nx, ny, nz;
    };

    // --- Helper to create layout for Vertex_P ---
    inline VertexLayout createLayout_P() {
        VertexLayout layout;
        layout.stride = sizeof(Vertex_P);
        layout.addElement(VertexAttribute::POSITION, offsetof(Vertex_P, x), sizeof(float) * 3, GL_FLOAT, 3);
        return layout;
    }

    // --- Helper to create layout for Vertex_PN ---
    inline VertexLayout createLayout_PN() {
        VertexLayout layout;
        layout.stride = sizeof(Vertex_PN);
        layout.addElement(VertexAttribute::POSITION, offsetof(Vertex_PN, x) , sizeof(float) * 3, GL_FLOAT, 3);
        layout.addElement(VertexAttribute::NORMAL  , offsetof(Vertex_PN, nx), sizeof(float) * 3, GL_FLOAT, 3);
        return layout;
    }

    // --- Helper to create layout for Vertex_PCTN ---
    inline VertexLayout createLayout_PCTN() {
        VertexLayout layout;
        layout.stride = sizeof(Vertex_PCTN);
        layout.addElement(VertexAttribute::POSITION  , offsetof(Vertex_PCTN, position), sizeof(M_VEC3)    , GL_FLOAT, 3);
        layout.addElement(VertexAttribute::COLOR     , offsetof(Vertex_PCTN, color   ), sizeof(M_VEC3)    , GL_FLOAT, 3, true);
        layout.addElement(VertexAttribute::TEXCOORD_0, offsetof(Vertex_PCTN, texCoord), sizeof(glm::vec2) , GL_FLOAT, 2);
        layout.addElement(VertexAttribute::NORMAL    , offsetof(Vertex_PCTN, normal  ), sizeof(M_VEC3)    , GL_FLOAT, 3);
        return layout;
    }
}
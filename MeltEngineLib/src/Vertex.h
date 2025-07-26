#pragma once
#include "Core.h"

namespace MELT
{
    #define MAX_BONE_INFLUENCE 4

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

    struct BoneInfo
    {
        int id;
        glm::mat4 offset;
    };

    struct Vertex_P
    {
        M_VEC3 position;
    };

    struct Vertex_PCTN
    {
        glm::vec3 position;
        glm::vec3 color;
        glm::vec2 texCoord;
        glm::vec3 normal;
    };

    struct Vertex_PCTN_TB_BW
    {
        M_VEC3 position  ;
        M_VEC3 color     ;
        M_VEC2 texCoord  ;
        M_VEC3 normal    ;
        M_VEC3 tangent   ;
        M_VEC3 bi_tangent;

        int   bond_ids[4];
        float weights [4];
    };

    struct Vertex_PCT
    {
        glm::vec3 position;
        glm::vec3 color;
        glm::vec2 texCoord;
    };

    struct Vertex_PN
    {
        float x, y, z;
        float nx, ny, nz;
    };

    // --- Helper to create layout for Vertex_P ---
    inline VertexLayout createLayout_P() {
        VertexLayout _layout;
        _layout.stride = sizeof(Vertex_P);
        _layout.addElement(VertexAttribute::POSITION, offsetof(Vertex_P, position), sizeof(M_VEC3), GL_FLOAT, 3);
        return _layout;
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
        VertexLayout _layout;
        _layout.stride = sizeof(Vertex_PCTN);
        _layout.addElement(VertexAttribute::POSITION  , offsetof(Vertex_PCTN, position), sizeof(M_VEC3)    , GL_FLOAT, 3);
        _layout.addElement(VertexAttribute::COLOR     , offsetof(Vertex_PCTN, color   ), sizeof(M_VEC3)    , GL_FLOAT, 3, true);
        _layout.addElement(VertexAttribute::TEXCOORD_0, offsetof(Vertex_PCTN, texCoord), sizeof(glm::vec2) , GL_FLOAT, 2);
        _layout.addElement(VertexAttribute::NORMAL    , offsetof(Vertex_PCTN, normal  ), sizeof(M_VEC3)    , GL_FLOAT, 3);
        return _layout;
    }

    inline VertexLayout createLayout_PCT() {
        VertexLayout _layout;
        _layout.stride = sizeof(Vertex_PCT);
        _layout.addElement(VertexAttribute::POSITION  , offsetof(Vertex_PCTN, position), sizeof(M_VEC3)    , GL_FLOAT, 3);
        _layout.addElement(VertexAttribute::COLOR     , offsetof(Vertex_PCTN, color   ), sizeof(M_VEC3)    , GL_FLOAT, 3, true);
        _layout.addElement(VertexAttribute::TEXCOORD_0, offsetof(Vertex_PCTN, texCoord), sizeof(glm::vec2) , GL_FLOAT, 2);
        return _layout;
    }

    inline void set_vertex_bone_to_default(Vertex_PCTN_TB_BW& _vertex)
    {
        for (int _i = 0; _i < MAX_BONE_INFLUENCE; ++_i)
        {
            _vertex.bond_ids[_i] = -1  ;
            _vertex.weights [_i] = 0.0f;
        }
    }

    inline void set_vertex_bone_data(Vertex_PCTN_TB_BW& _vertex, int _bone_id, float _weight)
    {
        for (int _i = 0; _i < MAX_BONE_INFLUENCE; ++_i)
        {
            if (_vertex.weights[_i] < 0)
            {
                _vertex.weights [_i] = _weight ;
                _vertex.bond_ids[_i] = _bone_id;
                break;
            }
        }
    }
}
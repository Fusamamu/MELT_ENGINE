#pragma once
#include "Core.h"
#include <GL/glew.h>

namespace MELT
{
    enum class ShaderType
    {
        NONE     = -1,
        VERTEX   = 0,
        GEOMETRY = 1,
        FRAGMENT = 2
    };

    class Shader
    {
    public:
        GLuint ID;

        explicit Shader(const std::string& _filePath);
        ~Shader();

        void use();

        void set_mat4_uniform_model                 (glm::mat4 _model              ) const;
        void set_mat4_uniform_view                  (glm::mat4 _view               ) const;
        void set_mat4_uniform_projection            (glm::mat4 _projection         ) const;
        void set_vec2_uniform_screen_size           (glm::vec2 _screenSize         ) const;
        void set_vec2_uniform_origin                (glm::vec2 _origin             ) const;
        void set_vec3_uniform_color                 (glm::vec3 _color              ) const;
        void set_vec3_uniform_object_color          (glm::vec3 _objectColor        ) const;
        void set_vec3_uniform_light_color           (glm::vec3 _lightColor         ) const;
        void set_vec3_uniform_light_world_position  (glm::vec3 _light_world_pos    ) const;
        void set_vec3_uniform_light_world_target    (glm::vec3 _light_world_target ) const;
        void set_vec3_uniform_camera_world_position (glm::vec3 _cameraWorldPos     ) const;
        void set_float_uniform_object_shininess     (float _shininess) const;

        friend std::ostream& operator<<(std::ostream& _os, Shader& _shader)
        {
            _os << "[ Vertex shader source ]" << '\n';
            _os << _shader.m_vertex_src << '\n';
            _os << '\n';
            _os << "[ Fragment shader source ]" << '\n';
            _os << _shader.m_fragment_src << '\n';

            return _os;
        }

    private:
        std::string m_vertex_src  ;
        std::string m_geometry_src;
        std::string m_fragment_src;

        GLint m_uniform_loc_model;
        GLint m_uniform_loc_view;
        GLint m_uniform_loc_projection;
        GLint m_UniformLoc_ScreenSize;
        GLint m_UniformLoc_Origin;
        GLint m_UniformLoc_Color;
        GLint m_UniformLoc_ObjectColor;
        GLint m_UniformLoc_ObjectShininess;
        GLint m_UniformLoc_LightColor;
        GLint m_UniformLoc_CameraWorldPosition;
        GLint m_uniform_loc_light_world_position;
        GLint m_uniform_loc_light_world_target;

        GLuint CreateShader(const std::string& _vertex_src, const std::string& _geometry_src, const std::string& _fragment_src);
        GLuint CompileShader(GLenum _shaderType, const std::string& _shaderSrc);
    };
}


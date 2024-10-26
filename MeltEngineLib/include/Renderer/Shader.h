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

        void Use();

        void SetMat4UniformModel              (glm::mat4 _model);
        void SetMat4UniformView               (glm::mat4 _view);
        void SetMat4UniformProjection         (glm::mat4 _projection);
        void SetVec2UniformScreenSize         (glm::vec2 _screenSize);
        void SetVec2UniformOrigin             (glm::vec2 _origin);
        void SetVec3UniformColor              (glm::vec3 _color);
        void SetVec3UniformObjectColor        (glm::vec3 _objectColor);
        void SetFloatUniformObjectShininess   (float _shininess);
        void SetVec3UniformLightColor         (glm::vec3 _lightColor);
        void SetVec3UniformLightWorldPosition (glm::vec3 _lightWorldPos);
        void SetVec3UniformCameraWorldPosition(glm::vec3 _cameraWorldPos);

        friend std::ostream& operator<<(std::ostream& _os, Shader& _shader)
        {
            _os << "[ Vertex shader source ]" << '\n';
            _os << _shader.m_VertexSrc << '\n';
            _os << '\n';
            _os << "[ Fragment shader source ]" << '\n';
            _os << _shader.m_FragmentSrc << '\n';

            return _os;
        }

    private:
        std::string m_VertexSrc;
        std::string m_GeometrySrc;
        std::string m_FragmentSrc;

        GLint m_UniformLoc_Model;
        GLint m_UniformLoc_View;
        GLint m_UniformLoc_Projection;
        GLint m_UniformLoc_ScreenSize;
        GLint m_UniformLoc_Origin;
        GLint m_UniformLoc_Color;
        GLint m_UniformLoc_ObjectColor;
        GLint m_UniformLoc_ObjectShininess;
        GLint m_UniformLoc_LightColor;
        GLint m_UniformLoc_CameraWorldPosition;
        GLint m_UniformLoc_LightWorldPosition;

        GLuint CreateShader(const std::string& _vertexSrc, const std::string& _geometrySrc, const std::string& _fragmentSrc);
        GLuint CompileShader(GLenum _shaderType, const std::string& _shaderSrc);
    };
}


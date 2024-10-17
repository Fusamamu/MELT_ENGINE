#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace MELT
{
    enum class ShaderType
    {
        NONE     = -1,
        VERTEX   = 0,
        FRAGMENT = 1
    };

    class Shader
    {
    public:
        GLuint ID;

        explicit Shader(const std::string& _filePath);
        ~Shader();

        void Use();

        void SetMat4UniformModel     (glm::mat4 _model);
        void SetMat4UniformView      (glm::mat4 _view);
        void SetMat4UniformProjection(glm::mat4 _projection);
        void SetVec2UniformScreenSize(glm::vec2 _screenSize);
        void SetVec2UniformOrigin    (glm::vec2 _origin);
        void SetVec3UniformColor     (glm::vec3 _color);

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
        std::string m_FragmentSrc;

        GLint m_UniformLoc_Model;
        GLint m_UniformLoc_View;
        GLint m_UniformLoc_Projection;
        GLint m_UniformLoc_ScreenSize;
        GLint m_UniformLoc_Origin;
        GLint m_UniformLoc_Color;

        GLuint CreateShader(const std::string& _vertexSrc, const std::string& _fragmentSrc);
        GLuint CompileShader(GLenum _shaderType, const std::string& _shaderSrc);
    };
}


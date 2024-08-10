#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <GL/glew.h>

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

        Shader(const std::string& _filePath);
        ~Shader();

        void Use();

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

        GLuint CreateShader(const std::string& _vertexSrc, const std::string& _fragmentSrc);
        GLuint CompileShader(GLenum _shaderType, const std::string& _shaderSrc);
    };
}


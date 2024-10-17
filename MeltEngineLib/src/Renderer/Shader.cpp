#include "Shader.h"

namespace MELT
{
    Shader::Shader(const std::string& _filePath)
    {
        std::ifstream _inputFile (_filePath);

        std::filesystem::path filepath = _filePath;
        if ( !exists(filepath) )
        {
            std::cout << "File path " << filepath << " at absolute location "
                      << absolute(filepath) << " does not exist\n";

            return;
        }

        if(!_inputFile.good())
        {
            std::cout << "File does not exist!" << std::endl;
            return;
        }

        if(!_inputFile.is_open())
        {
            std::cout << "input file not open!" << std::endl;
            return;
        }

        ShaderType _shaderType = ShaderType::NONE;

        std::stringstream _ss[2];

        std::string _line;
        while(std::getline(_inputFile, _line))
        {
            if(_line.find("#shader vertex") != std::string::npos)
            {
                _shaderType = ShaderType::VERTEX;
                continue;
            }

            if(_line.find("#shader fragment") != std::string::npos)
            {
                _shaderType = ShaderType::FRAGMENT;
                continue;
            }

            int _targetIndex = (int)(_shaderType);
            if(_targetIndex == -1)
                continue;

            _ss[_targetIndex] << _line << '\n';
        }

        m_VertexSrc   = _ss[(int)(ShaderType::VERTEX)]  .str();
        m_FragmentSrc = _ss[(int)(ShaderType::FRAGMENT)].str();

        _inputFile.close();

        ID = CreateShader(m_VertexSrc, m_FragmentSrc);

        m_UniformLoc_Model      = glGetUniformLocation(ID, "model");
        m_UniformLoc_View       = glGetUniformLocation(ID, "view");
        m_UniformLoc_Projection = glGetUniformLocation(ID, "proj");
        m_UniformLoc_ScreenSize = glGetUniformLocation(ID, "screenSize");
        m_UniformLoc_Origin     = glGetUniformLocation(ID, "origin");
        m_UniformLoc_Color      = glGetUniformLocation(ID, "Color");
    }

    Shader::~Shader()
    {
        glDeleteProgram(ID);
    }

    void Shader::Use()
    {
        glUseProgram(ID);
    }

    void Shader::SetMat4UniformModel(glm::mat4 _model)
    {
        glUniformMatrix4fv(m_UniformLoc_Model, 1, GL_FALSE, glm::value_ptr(_model));
    }

    void Shader::SetMat4UniformView(glm::mat4 _view)
    {
        glUniformMatrix4fv(m_UniformLoc_View, 1, GL_FALSE, glm::value_ptr(_view));
    }

    void Shader::SetMat4UniformProjection(glm::mat4 _projection)
    {
        glUniformMatrix4fv(m_UniformLoc_Projection, 1, GL_FALSE, glm::value_ptr(_projection));
    }

    void Shader::SetVec2UniformScreenSize(glm::vec2 _screenSize)
    {
        glUniform2f(m_UniformLoc_ScreenSize, _screenSize.x, _screenSize.y);
    }

    void Shader::SetVec2UniformOrigin(glm::vec2 _origin)
    {
        glUniform2f(m_UniformLoc_Origin, _origin.x, _origin.y);
    }

    void Shader::SetVec3UniformColor(glm::vec3 _color)
    {
        glUniform3f(m_UniformLoc_Color, _color.r, _color.g, _color.b);
    }

    GLuint Shader::CreateShader(const std::string& _vertexSrc, const std::string& _fragmentSrc)
    {
        GLuint _vertexShader   = CompileShader(GL_VERTEX_SHADER  , _vertexSrc  );
        GLuint _fragmentShader = CompileShader(GL_FRAGMENT_SHADER, _fragmentSrc);

        GLuint _shaderProgram = glCreateProgram();
        glAttachShader(_shaderProgram, _vertexShader);
        glAttachShader(_shaderProgram, _fragmentShader);
        glLinkProgram(_shaderProgram);

        GLint _success;
        glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &_success);
        if (!_success) {
            char infoLog[512];
            glGetProgramInfoLog(_shaderProgram, 512, nullptr, infoLog);
            std::cerr << "Program Linking Error: " << infoLog << std::endl;
        }

        glDeleteShader(_vertexShader);
        glDeleteShader(_fragmentShader);

        return _shaderProgram;
    }

    GLuint Shader::CompileShader(GLenum _shaderType, const std::string &_shaderSrc)
    {
        GLuint _shader = glCreateShader(_shaderType);

        const char* _src = _shaderSrc.c_str();
        glShaderSource(_shader, 1, &_src, nullptr);
        glCompileShader(_shader);

        GLint _success;
        glGetShaderiv(_shader, GL_COMPILE_STATUS, &_success);
        if(!_success)
        {
            char _infoLog[512];
            glGetShaderInfoLog(_shader, 512, nullptr, _infoLog);
            std::cerr << "Shader Compilation Error: " << _infoLog << std::endl;
        }

        return _shader;
    }
}
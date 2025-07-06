#include "Shader.h"

namespace MELT
{
    Shader::Shader(const std::string& _filePath)
    {
        //uuid = generate_uuid(reinterpret_cast<uintptr_t>(this));

        std::ifstream _inputFile (_filePath);

        std::filesystem::path filepath = _filePath;
        if (!exists(filepath))
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

        std::stringstream _ss[3];

        std::string _line;
        while(std::getline(_inputFile, _line))
        {
            if(_line.find("#shader vertex") != std::string::npos)
            {
                _shaderType = ShaderType::VERTEX;
                continue;
            }

            if(_line.find("#shader geometry") != std::string::npos)
            {
                _shaderType = ShaderType::GEOMETRY;
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

        m_vertex_src   = _ss[(int)(ShaderType::VERTEX)]  .str();
        m_geometry_src = _ss[(int)(ShaderType::GEOMETRY)].str();
        m_fragment_src = _ss[(int)(ShaderType::FRAGMENT)].str();

        _inputFile.close();

        ID = CreateShader(m_vertex_src, m_geometry_src, m_fragment_src);

        m_uniform_loc_model                 = glGetUniformLocation(ID, "model"             );
        m_uniform_loc_view                  = glGetUniformLocation(ID, "view"              );
        m_uniform_loc_projection            = glGetUniformLocation(ID, "proj"              );
        m_UniformLoc_ScreenSize             = glGetUniformLocation(ID, "screenSize"        );
        m_UniformLoc_Origin                 = glGetUniformLocation(ID, "origin"            );
        m_UniformLoc_Color                  = glGetUniformLocation(ID, "Color"             );
        m_UniformLoc_ObjectColor            = glGetUniformLocation(ID, "objectColor"       );
        m_UniformLoc_ObjectShininess        = glGetUniformLocation(ID, "shininess"         );
        m_UniformLoc_LightColor             = glGetUniformLocation(ID, "lightColor"        );
        m_UniformLoc_CameraWorldPosition    = glGetUniformLocation(ID, "camera_world_pos"  );
        m_uniform_loc_light_world_position  = glGetUniformLocation(ID, "light_world_pos"   );
        m_uniform_loc_light_world_target    = glGetUniformLocation(ID, "light_world_target");
    }

    Shader::~Shader()
    {
        glDeleteProgram(ID);
    }

    void Shader::use()
    {
        glUseProgram(ID);
    }

    void Shader::set_mat4_uniform_model(glm::mat4 _model) const
    {
        glUniformMatrix4fv(m_uniform_loc_model, 1, GL_FALSE, glm::value_ptr(_model));
    }

    void Shader::set_mat4_uniform_view(glm::mat4 _view) const
    {
        glUniformMatrix4fv(m_uniform_loc_view, 1, GL_FALSE, glm::value_ptr(_view));
    }

    void Shader::set_mat4_uniform_projection(glm::mat4 _projection) const
    {
        glUniformMatrix4fv(m_uniform_loc_projection, 1, GL_FALSE, glm::value_ptr(_projection));
    }

    void Shader::set_vec2_uniform_screen_size(glm::vec2 _screenSize) const
    {
        glUniform2f(m_UniformLoc_ScreenSize, _screenSize.x, _screenSize.y);
    }

    void Shader::set_vec2_uniform_origin(glm::vec2 _origin) const
    {
        glUniform2f(m_UniformLoc_Origin, _origin.x, _origin.y);
    }

    void Shader::set_vec3_uniform_color(glm::vec3 _color) const
    {
        glUniform3f(m_UniformLoc_Color, _color.r, _color.g, _color.b);
    }

    void Shader::set_vec3_uniform_object_color(glm::vec3 _objectColor) const
    {
        glUniform3f(m_UniformLoc_ObjectColor, _objectColor.r, _objectColor.g, _objectColor.b);
    }

    void Shader::set_float_uniform_object_shininess(float _shininess) const
    {
        glUniform1f(m_UniformLoc_ObjectShininess, _shininess);
    }

    void Shader::set_vec3_uniform_light_color(glm::vec3 _lightColor) const
    {
        glUniform3f(m_UniformLoc_LightColor, _lightColor.r, _lightColor.g, _lightColor.b);
    }

    void Shader::set_vec3_uniform_light_world_position(glm::vec3 _lightWorldPos) const
    {
        glUniform3f(m_uniform_loc_light_world_position, _lightWorldPos.x, _lightWorldPos.y, _lightWorldPos.z);
    }

    void Shader::set_vec3_uniform_light_world_target(glm::vec3 _light_world_target) const
    {
        glUniform3f(m_uniform_loc_light_world_target, _light_world_target.x, _light_world_target.y, _light_world_target.z);
    }


    void Shader::set_vec3_uniform_camera_world_position(glm::vec3 _cameraWorldPos) const
    {
        //glUniform3f(m_UniformLoc_Color, _cameraWorldPos.x, _cameraWorldPos.y, _cameraWorldPos.x);
    }

    void Shader::set_uniform(const std::string& _name, int _iv) const
    {
        glUniform1i(glGetUniformLocation(ID, "u_texture"), _iv); 
    }

    void Shader::set_uniform(const std::string& _name, float _fv) const
    {

    }

    void Shader::set_uniform(const std::string& _name, M_VEC4 _vec4) const
    {

    }

    GLuint Shader::CreateShader(const std::string& _vertex_src, const std::string& _geometry_src, const std::string& _fragment_src)
    {
        GLuint _vertexShader   = CompileShader(GL_VERTEX_SHADER  , _vertex_src  );
        GLuint _fragmentShader = CompileShader(GL_FRAGMENT_SHADER, _fragment_src);

        GLuint _shaderProgram = glCreateProgram();
        glAttachShader(_shaderProgram, _vertexShader  );
        glAttachShader(_shaderProgram, _fragmentShader);

        if(!_geometry_src.empty())
        {
            GLuint _geometryShader = CompileShader(GL_GEOMETRY_SHADER, _geometry_src);
            glAttachShader(_shaderProgram, _geometryShader);
        }

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

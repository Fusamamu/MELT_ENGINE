#include "Material.h"

namespace MELT::GRAPHIC
{
    void Material::bind()
    {
        p_shader->use(); // Bind shader program

        for (auto& [name, value] : vec4_uniforms)
            p_shader->set_uniform(name, value);

        for (auto& [name, value] : float_uniforms)
            p_shader->set_uniform(name, value);

        for (auto& [name, value] : int_uniforms)
            p_shader->set_uniform(name, value);

        int _tex_slot = 0;

        for (auto& [name, _texture] : texture_uniforms)
        {
            _texture->bind(_tex_slot);
            p_shader->set_uniform(name, _tex_slot);
            _tex_slot++;
        }

        if (transparent)
        {
            glEnable   (GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
        else
        {
            glDisable(GL_BLEND);
        }

        if (double_sided)
            glDisable(GL_CULL_FACE);
        else
            glEnable(GL_CULL_FACE);
    }
    
    std::string create_material()
    {
        YAML::Emitter _out;
        _out << YAML::BeginMap;
        _out << YAML::Key << "Material" << YAML::Value << YAML::BeginMap;
        
            _out << YAML::Key << "name"         << YAML::Value << "default_material";
            _out << YAML::Key << "shader"       << YAML::Value << "phong.glsl";
            _out << YAML::Key << "render_queue" << YAML::Value << "opaque";
            _out << YAML::Key << "properties"   << YAML::Value << YAML::BeginMap;

                _out << YAML::Key << "base_color" << YAML::Value << YAML::Flow 
                    << YAML::BeginSeq << 0.0 << 0.0 << 0.0 << 1.0 << YAML::EndSeq;
                _out << YAML::Key << "albedo_texture" << YAML::Value << "white_texture.png";

            _out << YAML::EndMap; 

        _out << YAML::EndMap;
        _out << YAML::EndMap;
        
        return std::string(_out.c_str());
    }
}

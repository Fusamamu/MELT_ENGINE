#include "Material.h"

namespace MELT::GRAPHIC
{
    void Material::bind()
    {
        mp_cached_shader->use();

        for (auto& [name, value] : vec4_uniforms)
            mp_cached_shader->set_uniform(name, value);

        for (auto& [name, value] : float_uniforms)
            mp_cached_shader->set_uniform(name, value);

        for (auto& [name, value] : int_uniforms)
            mp_cached_shader->set_uniform(name, value);

        int _tex_slot = 0;

        for (auto& [name, _texture] : texture_uniforms)
        {
            _texture->bind(_tex_slot);
            mp_cached_shader->set_uniform(name, _tex_slot);
            _tex_slot++;
        }

        //if (transparent)
        //{
        //    glEnable   (GL_BLEND);
        //    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //}
        //else
        //{
        //    glDisable(GL_BLEND);
        //}

        //if (double_sided)
        //    glDisable(GL_CULL_FACE);
        //else
        //    glEnable(GL_CULL_FACE);
    }
    
    std::string create_material()
    {
        YAML::Emitter _out;
        _out << YAML::BeginMap;
        _out << YAML::Key << "Material" << YAML::Value << YAML::BeginMap;
        
            _out << YAML::Key << "name"          << YAML::Value << "new_default_material";
            _out << YAML::Key << "uuid"          << YAML::Value << MELT::generate_uuid(1).c_str();
            _out << YAML::Key << "shader_handle" << YAML::Value << AssetRegistry::instance().get_meta_by_name<Shader>("phong.glsl").uuid;

            _out << YAML::Key << "render_queue" << YAML::Value << "opaque";
            _out << YAML::Key << "properties"   << YAML::Value << YAML::BeginMap;

                _out << YAML::Key << "color"   << YAML::Value << YAML::Flow 
                    << YAML::BeginSeq << 0.0 << 0.0 << 0.0 << 1.0 << YAML::EndSeq;
                _out << YAML::Key << "texture_handle" << YAML::Value << AssetRegistry::instance().get_meta_by_name<Texture>("checker.png").uuid;

            _out << YAML::EndMap; 

        _out << YAML::EndMap;
        _out << YAML::EndMap;
        
        return std::string(_out.c_str());
    }

    Shader* Material::get_cached_shader()
    {
        return mp_cached_shader;
    }

    void Material::validate()
    {
        if (mp_cached_shader == nullptr)
            mp_cached_shader = shader_handle.get();

        for (auto& [_name, _p_texture] : texture_uniforms)
        {
            // if (_p_texture == nullptr)
            //     _p_texture = textru
        }
    }
}

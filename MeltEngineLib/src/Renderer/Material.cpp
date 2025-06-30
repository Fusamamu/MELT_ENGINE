#include "Material.h"

namespace MELT::GRAPHIC
{
    void Material::bind()
    {
        p_shader->use(); 

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
            _out << YAML::Key << "uuid"         << YAML::Value << MELT::generate_uuid(1).c_str();
            _out << YAML::Key << "shader"       << YAML::Value << "phong.glsl";
            _out << YAML::Key << "render_queue" << YAML::Value << "opaque";
            _out << YAML::Key << "properties"   << YAML::Value << YAML::BeginMap;

                _out << YAML::Key << "color"   << YAML::Value << YAML::Flow 
                    << YAML::BeginSeq << 0.0 << 0.0 << 0.0 << 1.0 << YAML::EndSeq;
                _out << YAML::Key << "texture" << YAML::Value << "white_texture.png";

            _out << YAML::EndMap; 

        _out << YAML::EndMap;
        _out << YAML::EndMap;
        
        return std::string(_out.c_str());
    }

    Material load_material(const std::string& _mat_file)
    {
        Material _material;
        YAML::Node _root = YAML::Load(_mat_file);

        auto material_node = _root["Material"];

        if (!material_node)
            throw std::runtime_error("Invalid material file: 'Material' root not found.");

        _material.name         = material_node["name"].as<std::string>();
        _material.uuid         = material_node["uuid"].as<std::string>();
        _material.shader_name  = material_node["shader"].as<std::string>();
        // mat.render_queue = material_node["render_queue"].as<std::string>();

        auto props = material_node["properties"];
        if (props)
        {
            if (props["color"] && props["color"].IsSequence() && props["color"].size() == 4)
            {
                glm::vec4 _color = glm::vec4(
                    props["color"][0].as<float>(),
                    props["color"][1].as<float>(),
                    props["color"][2].as<float>(),
                    props["color"][3].as<float>()
                );

                _material.vec4_uniforms["color"] = _color;
            }

            // if (props["texture"]) {
            //     _material.texture = props["texture"].as<std::string>();
            // }
        }
        return _material;
    }
}

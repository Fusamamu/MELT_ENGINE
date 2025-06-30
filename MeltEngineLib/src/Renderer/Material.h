#ifndef MATERIAL_H
#define MATERIAL_H

#include "Core.h"
#include "Shader.h"
#include "Texture.h"

namespace MELT::GRAPHIC
{
    namespace UNIFORMS
    {
        constexpr const char* COLOR        = "u_color";
        constexpr const char* ALBEDO_COLOR = "u_albedo_color";
        constexpr const char* ALBEDO_MAP   = "u_albedo_map"  ;
        constexpr const char* METALLIC     = "u_metallic"    ;
        constexpr const char* ROUGHNESS    = "u_roughness"   ;
    }

    class Material
    {
    public:
        std::string name;

        UUID uuid;

        std::string shader_name;

        Shader* p_shader;

        bool transparent  = false;
        bool double_sided = false;

        std::unordered_map<std::string, glm::vec4> vec4_uniforms;
        std::unordered_map<std::string, float>     float_uniforms;
        std::unordered_map<std::string, int>       int_uniforms;
        std::unordered_map<std::string, Texture*>  texture_uniforms; 

        Material() = default;
        ~Material() = default;
    
        void bind();
    };
    
    std::string create_material();
}

#endif 

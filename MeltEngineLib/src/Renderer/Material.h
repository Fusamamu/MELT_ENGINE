#ifndef MATERIAL_H
#define MATERIAL_H

#include "Core.h"
#include "AssetRegistry.h"
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
        UUID uuid;
        std::string name;

        AssetHandle<Shader> shader_handle;

        bool transparent  = false;
        bool double_sided = false;

        std::unordered_map<std::string, glm::vec4> vec4_uniforms;
        std::unordered_map<std::string, float>     float_uniforms;
        std::unordered_map<std::string, int>       int_uniforms;
        std::unordered_map<std::string, Texture*>  texture_uniforms; 

        Material() = default;
        ~Material() = default;
    
        void bind();
        void unbind();
        void validate();

    private:
        Shader* mp_cached_shader;
    };
    
    std::string create_material();
}

#endif 

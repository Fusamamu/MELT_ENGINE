#ifndef SHADERPREVIEW_H
#define SHADERPREVIEW_H

#include "Core.h"
#include "Camera.h"
#include "Shader.h"
#include "FrameBuffer.h"
#include "Cube.h"
#include "MeshRenderer.h"

namespace MELT
{
    class ShaderPreview
    {
    public:
        Camera target_camera;

        Shader* p_target_shader;
        FrameBuffer preview_fbo;

        glm::vec4 clear_color;

        MeshRenderer preview_renderer;

        ShaderPreview () = default;
        ~ShaderPreview() = default;

        void init();
        void render();

        GRAPHIC::Material& get_preview_material();
        void set_preview_target_material(GRAPHIC::Material* _material);
    private:
        GRAPHIC::Material* mp_target_material;
    };
}

#endif

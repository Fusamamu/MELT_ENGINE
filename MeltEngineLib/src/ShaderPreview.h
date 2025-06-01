#ifndef SHADERPREVIEW_H
#define SHADERPREVIEW_H

#include "Core.h"
#include "Camera.h"
#include "Shader.h"
#include "FrameBuffer.h"
#include "Cube.h"

namespace MELT
{
    class ShaderPreview
    {
    public:
        Camera  target_camera;
        Shader* p_target_shader;
        FrameBuffer preview_fbo;

        glm::vec4 clear_color;

        Cube cube;

        ShaderPreview () = default;
        ~ShaderPreview() = default;

        void init();
        void Render() const;
    };
}

#endif

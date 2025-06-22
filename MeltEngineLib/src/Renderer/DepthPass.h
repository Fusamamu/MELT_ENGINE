#ifndef DEPTHPASS_H
#define DEPTHPASS_H

#include "Core.h"
#include "Scene.h"
#include "Camera.h"
#include "Shader.h"
#include "FrameBuffer.h"
#include "Cube.h"
#include "MeshRenderer.h"

namespace MELT
{
    class DepthPass
    {
    public:
        Camera  target_camera;
        Shader* p_target_shader;
        FrameBuffer frame_buffer;

        glm::vec4 clear_color;

        MeshRenderer preview_renderer;

        DepthPass () = default;
        ~DepthPass() = default;

        void init();
        void Render(const Scene& _scene);
    };
}

#endif //DEPTHPASS_H

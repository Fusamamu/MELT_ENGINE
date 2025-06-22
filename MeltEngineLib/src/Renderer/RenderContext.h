#ifndef RENDER_CONTEXT_H
#define RENDER_CONTEXT_H

#include "Camera.h"

namespace MELT::GRAPHIC
{
    class RenderContext
    {
    public:
        glm::mat4 view;
        glm::mat4 projection;
        glm::vec3 cameraPosition;

        RenderContext() = default;
        ~RenderContext() = default;
    };
}

#endif

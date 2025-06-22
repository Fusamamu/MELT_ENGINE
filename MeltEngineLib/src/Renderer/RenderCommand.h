#ifndef RENDER_COMMAND_H
#define RENDER_COMMAND_H

#include "Shader.h"
#include "Mesh.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "RenderContext.h"

namespace MELT::GRAPHIC
{
    class ICommand
    {
    public:
        virtual void execute() = 0;
        virtual ~ICommand() = default;
    };

    class RenderGridGizmosCommand: public ICommand
    {
    public:
        std::string name = "Render grid gizmos command";
        Shader       * p_shader;
        MeshRenderer * p_mesh_renderer;
        RenderContext* p_context;

        glm::mat4 model_mat;
        glm::mat4 view_mat;
        glm::mat4 projection_mat;

        RenderGridGizmosCommand()  = default;
        ~RenderGridGizmosCommand() = default;

        void execute() override
        {
            p_shader->use();
            p_shader->set_mat4_uniform_model     (glm::translate(glm::mat4(1.0f), glm::vec3 (0.0, 0.0, 0.0)));
            p_shader->set_mat4_uniform_view      (view_mat);
            p_shader->set_mat4_uniform_projection(projection_mat);
            p_mesh_renderer->draw();
        }
    };

    class SetStencilCommand : public ICommand
    {
    public:
        GLenum func;
        GLint ref;
        GLuint mask;
        GLuint writeMask;

        SetStencilCommand(GLenum f, GLint r, GLuint m, GLuint wm)
            : func(f), ref(r), mask(m), writeMask(wm) {}

        void execute() override
        {
            glStencilMask(writeMask);
            glStencilFunc(func, ref, mask);
        }
    };

    class DisableDepthCommand : public ICommand
    {
    public:
        DisableDepthCommand() = default;
        void execute() override { glDisable(GL_DEPTH_TEST); }
    };

    class EnableDepthCommand : public ICommand
    {
    public:
        EnableDepthCommand() = default;
        void execute() override { glEnable(GL_DEPTH_TEST); }
    };

    class DrawMeshCommand : public ICommand
    {
    public:
        std::string name = "Draw mesh command";
        Shader       * p_shader;
        MeshRenderer * p_mesh_renderer;
        RenderContext* p_context;

        glm::mat4 model_mat;
        glm::mat4 view_mat;
        glm::mat4 projection_mat;

        DrawMeshCommand()  = default;
        ~DrawMeshCommand() = default;

        void execute() override
        {
            p_shader->use();
            p_shader->set_mat4_uniform_model     (model_mat);
            p_shader->set_mat4_uniform_view      (view_mat);
            p_shader->set_mat4_uniform_projection(projection_mat);
            p_mesh_renderer->draw();
        }
    };

    class DrawOutlineCommand : public ICommand
    {
    public:
        std::string name = "Draw outline command";
        Shader       * p_shader;
        MeshRenderer * p_mesh_renderer;
        RenderContext* p_context;

        glm::mat4 model_mat;
        glm::mat4 view_mat;
        glm::mat4 projection_mat;

        void execute() override
        {
            p_shader->use();
            p_shader->set_mat4_uniform_model     (model_mat);
            p_shader->set_mat4_uniform_view      (view_mat);
            p_shader->set_mat4_uniform_projection(projection_mat);
            p_mesh_renderer->draw();
        }
    };
}

#endif

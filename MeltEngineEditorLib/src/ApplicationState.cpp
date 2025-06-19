#include "ApplicationState.h"
#include "MeltEngineEditor.h"

namespace MELT_EDITOR
{
    void ApplicationModeManager::update(float dt)
    {
        if (!m_current_mode)
            return;
        while (m_current_mode->editor_owner->is_running)
        {
            m_current_mode->update(dt);
            m_current_mode->render();
            SDL_Delay(16);
        }
    }


#pragma region Editor mode implementation
    void EditorMode::on_enter()
    {
    }

    void EditorMode::update(float dt)
    {
        SDL_Event m_event;

        MELT::Input.ClearInput();
        while(SDL_PollEvent(&m_event))
        {
            MELT::Input.Update(m_event);

            editor_owner->update_input(m_event);

            switch(m_event.type)
            {
                case SDL_QUIT:
                    editor_owner->is_running = false;
                break;
                case SDL_WINDOWEVENT:
                    if(m_event.window.event == SDL_WINDOWEVENT_RESIZED)
                    {
                        GLsizei _width  = m_event.window.data1;
                        GLsizei _height = m_event.window.data2;
                        editor_owner->engine->manager_registry.get<MELT::RenderPipeline>()->rescale_frame_buffers(2 * _width, 2 * _height);
                    }
                break;
            }
        }
        MELT::Input.CheckMouseHoldStates();

        if(MELT::Input.IsKeyPressed(SDL_SCANCODE_ESCAPE))
            editor_owner->is_running = false;

        editor_owner->engine->update_editor_logic();
    }

    void EditorMode::render()
    {
        editor_owner->engine->begin_frame();
        editor_owner->engine->render_frame();
        editor_owner->update_gui();
        editor_owner->engine->end_frame();
    }

    void EditorMode::on_exit()
    {
    }
#pragma endregion

#pragma region Gameplay mode implementation
    void GameplayMode::on_enter()
    {
        editor_owner->engine->Logger.log("Gameplay mode entered");
    }

    void GameplayMode::update(float dt)
    {
        editor_owner->engine->Logger.log("Gameplay mode updated");

        SDL_Event m_event;

        MELT::Input.ClearInput();
        while(SDL_PollEvent(&m_event))
        {
            MELT::Input.Update(m_event);
            editor_owner->update_input(m_event);

            switch(m_event.type)
            {
                case SDL_QUIT:
                    editor_owner->is_running = false;
                break;
                case SDL_WINDOWEVENT:
                    if(m_event.window.event == SDL_WINDOWEVENT_RESIZED)
                    {
                        GLsizei _width  = m_event.window.data1;
                        GLsizei _height = m_event.window.data2;
                        editor_owner->engine->manager_registry.get<MELT::RenderPipeline>()->rescale_frame_buffers(2 * _width, 2 * _height);
                    }
                break;
            }
        }
        MELT::Input.CheckMouseHoldStates();

        if(MELT::Input.IsKeyPressed(SDL_SCANCODE_ESCAPE))
            editor_owner->is_running = false;

        editor_owner->engine->update_logic();
    }

    void GameplayMode::render()
    {
        editor_owner->engine->begin_frame();
        editor_owner->engine->render_frame();
        editor_owner->update_gui();
        editor_owner->engine->end_frame();
    }

    void GameplayMode::on_exit()
    {
    }
#pragma endregion
}
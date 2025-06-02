#include "ApplicationState.h"
#include "MeltEngineEditor.h"

namespace MELT_EDITOR
{
#pragma region Editor mode implementation
    void EditorMode::OnEnter()
    {

    }

    void EditorMode::update(float dt)
    {
        SDL_Event m_event;

        bool m_is_running = true;

        while (m_is_running)
        {
            MELT::Input.ClearInput();
            while(SDL_PollEvent(&m_event))
            {
                MELT::Input.Update(m_event);

                editor_owner->update_input(m_event);

                switch(m_event.type)
                {
                    case SDL_QUIT:
                        m_is_running = false;
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
                m_is_running = false;

            editor_owner->engine->update_logic();
            editor_owner->engine->begin_frame();
            editor_owner->engine->render_frame();
            editor_owner->update_gui();
            editor_owner->engine->end_frame();

            SDL_Delay(16);
        }
    }

    void EditorMode::OnExit()
    {

    }
#pragma endregion

#pragma region Gameplay mode implementation
    void GameplayMode::OnEnter()
    {

    }

    void GameplayMode::update(float dt)
    {
        SDL_Event m_event;
        bool m_is_running = true;

        while (m_is_running)
        {
            MELT::Input.ClearInput();
            while(SDL_PollEvent(&m_event))
            {
                MELT::Input.Update(m_event);
                editor_owner->update_input(m_event);

                switch(m_event.type)
                {
                    case SDL_QUIT:
                        m_is_running = false;
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
                m_is_running = false;

            editor_owner->engine->update_logic();
            editor_owner->engine->begin_frame();
            editor_owner->engine->render_frame();
            editor_owner->update_gui();
            editor_owner->engine->end_frame();

            SDL_Delay(16);
        }
    }

    void GameplayMode::OnExit()
    {

    }
#pragma region Gameplay mode implementation
}
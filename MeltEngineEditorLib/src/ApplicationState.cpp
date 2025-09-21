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

#pragma region Tile Editor mode implementation
    void TileEditorMode::on_enter()
    {
    }

    void TileEditorMode::update(float dt)
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

        MELT::Scene* _working_scene = editor_owner->engine->manager_registry.get<MELT::SceneManager>()->working_scene;
        auto _view = _working_scene->ecs_registry.view<MELT::Transform, MELT::Tile, MELT::NodeEditor>();




        if(MELT::Input.IsMouseButtonPressed(SDL_BUTTON_LEFT))
        {
            float _closestDistance = FLT_MAX;
            MELT::Ray _ray = MELT::RayCast::screen_to_world_ray(MELT::InputSystem::Instance().MouseScreenPosition, editor_owner->engine->main_camera);

            for (auto _entity : _view)
            {
                auto& _transform = _working_scene->ecs_registry.get<MELT::Transform >(_entity);
                auto& _tile      = _working_scene->ecs_registry.get<MELT::Tile      >(_entity);
                auto& _node      = _working_scene->ecs_registry.get<MELT::NodeEditor>(_entity);

                //Need to check against aabb
                auto _minBounds = _transform.position + M_VEC3(-0.5, -0.5, -0.5);
                auto _maxBounds = _transform.position + M_VEC3( 0.5,  0.5,  0.5);

                if (MELT::RayCast::RayIntersectsAABB(_ray.origin, _ray.direction, _minBounds, _maxBounds))
                {
                    float _distance = glm::distance(_ray.origin, _transform.position);
                    if (_distance < _closestDistance)
                    {
                        _closestDistance = _distance;


                        auto& _ctx = _working_scene->ecs_registry.ctx();
                        if (_ctx.contains<MELT::BlockTileGrid>())
                        {
                            auto& _block_tile = _ctx.get<MELT::BlockTileGrid>();

                            MELT::SceneNode& _node = _working_scene->create_node("Entity");

                            M_VEC3 _position = _transform.position;
                            _position.y += 1.0f;
                            _block_tile.grid.build_default(_node, _position, M_VEC3_I(_tile.idx, _tile.idy + 1, _tile.idz));
                            _block_tile.grid.add_node_at  (_node, _tile.idx, _tile.idy + 1, _tile.idz);
                        }





                        editor_owner->engine->Logger.log(_node.id);
                        break;
                    }
                }
            }
        }


        switch (edit_mode)
        {
            case EDIT_MODE::ADD_TILE:
                break;
            case EDIT_MODE::REMOVE_TILE:
                break;
            case EDIT_MODE::PLACE_TIE:
                break;
        }
    }

    void TileEditorMode::render()
    {
        editor_owner->engine->begin_frame();
        editor_owner->engine->render_frame();
        editor_owner->update_gui();
        editor_owner->engine->end_frame();
    }

    void TileEditorMode::on_exit()
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
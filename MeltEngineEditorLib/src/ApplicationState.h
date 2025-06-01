#ifndef APPLICATIONSTATE_H
#define APPLICATIONSTATE_H

namespace MELT_EDITOR
{
    enum class ApplicationState
    {
        NONE,
        EDITOR,
        GAMEPLAY,
        PAUSE
    };

    class ApplicationMode
    {
    public:
        virtual void OnEnter() = 0;
        virtual void OnExit()  = 0;
        virtual void Update(float _dt) = 0;
        virtual ~ApplicationMode() = default;
    };

    class EditorMode : public ApplicationMode {
    public:
        void OnEnter() override;
        void Update(float dt) override;
        void OnExit() override;
    };

    class GameplayMode : public ApplicationMode {
    public:
        void OnEnter() override;
        void Update(float dt) override;
        void OnExit() override;
    };

    class ApplicationModeManager
    {
    public:
        void ChangeState(ApplicationState _new_state)
        {
            if (m_current_mode)
                m_current_mode->OnExit();

            switch (_new_state) {
                case ApplicationState::EDITOR:
                    m_current_mode = std::make_unique<EditorMode>();
                    break;
                case ApplicationState::GAMEPLAY:
                    m_current_mode = std::make_unique<GameplayMode>();
                    break;
            }
            m_current_state = _new_state;
            m_current_mode->OnEnter();
        }

        void Update(float dt)
        {
            if (m_current_mode)
                m_current_mode->Update(dt);
        }
    private:
        ApplicationState m_current_state { ApplicationState::NONE };
        std::unique_ptr<ApplicationMode> m_current_mode;
    };

}

#endif

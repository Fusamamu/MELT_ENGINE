#ifndef APPLICATIONSTATE_H
#define APPLICATIONSTATE_H
#include "Core.h"

namespace MELT_EDITOR
{
    class Editor;

    class ApplicationMode
    {
    public:
        Editor* editor_owner;

        ApplicationMode(Editor* _editor): editor_owner(_editor){ }
        virtual void OnEnter() = 0;
        virtual void OnExit()  = 0;
        virtual void update(float _dt) = 0;
        virtual ~ApplicationMode() = default;
    };

    class EditorMode : public ApplicationMode {
    public:
        EditorMode(Editor* _editor): ApplicationMode(_editor) { }
        void OnEnter() override;
        void update(float dt) override;
        void OnExit() override;
    };

    class GameplayMode : public ApplicationMode {
    public:
        GameplayMode(Editor* _editor): ApplicationMode(_editor) { }
        void OnEnter() override;
        void update(float dt) override;
        void OnExit() override;
    };

    class ApplicationModeManager
    {
    public:
        ApplicationModeManager()  = default;
        ~ApplicationModeManager() = default;

        template<typename T>
        bool is_current_mode()
        {
            std::type_index _index(typeid(T));
            auto _it = m_mode_table.find(_index);
            if (_it != m_mode_table.end())
                return m_current_mode == _it->second.get();
            return false;
        }

        template<typename T, typename... Args>
        void add_state(Args&&... _args)
        {
            static_assert(std::is_base_of<ApplicationMode, T>::value, "T must be derived from ApplicationMode");
            std::type_index index(typeid(T));
            m_mode_table.try_emplace(index, std::make_unique<T>(std::forward<Args>(_args)...));
        }

        template<typename T>
        void set_initial_state()
        {
            std::type_index index(typeid(T));
            auto _it = m_mode_table.find(index);
            if (_it != m_mode_table.end())
            {
                m_current_mode = _it->second.get();
                m_current_mode->OnEnter();
            }
        }

        template<typename T>
        void change_state()
        {
            std::type_index index(typeid(T));
            auto _it = m_mode_table.find(index);
            if (_it != m_mode_table.end())
            {
                if (m_current_mode)
                    m_current_mode->OnExit();

                m_current_mode = _it->second.get();
                m_current_mode->OnEnter();
            }
        }

        void update(float dt)
        {
            if (m_current_mode)
                m_current_mode->update(dt);
        }

    private:
        ApplicationMode* m_current_mode = nullptr;
        std::unordered_map<std::type_index, std::unique_ptr<ApplicationMode>> m_mode_table;
    };
}
#endif

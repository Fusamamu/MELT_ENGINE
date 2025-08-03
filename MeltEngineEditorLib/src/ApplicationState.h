#ifndef APPLICATION_STATE_H
#define APPLICATION_STATE_H

#include "Core.h"

namespace MELT_EDITOR
{
    class Editor;

    class ApplicationMode
    {
    public:
        Editor* editor_owner;

        bool running = false;

        ApplicationMode(Editor* _editor): editor_owner(_editor){ }
        virtual ~ApplicationMode() = default;

        virtual void on_enter() = 0;
        virtual void on_exit()  = 0;
        virtual void update(float _dt) = 0;
        virtual void render() = 0;
    };

    class EditorMode : public ApplicationMode {
    public:
        EditorMode(Editor* _editor): ApplicationMode(_editor) { }
        void on_enter() override;
        void on_exit() override;
        void update(float dt) override;
        void render() override;
    };

    class GameplayMode : public ApplicationMode {
    public:
        GameplayMode(Editor* _editor): ApplicationMode(_editor) { }
        void on_enter() override;
        void update(float dt) override;
        void on_exit() override;
        void render() override;
    };

    class TileEditorMode : public ApplicationMode
    {
    public:
        enum class EDIT_MODE
        {
            ADD_TILE = 0,
            REMOVE_TILE,
            PLACE_TIE
        };

        EDIT_MODE edit_mode = EDIT_MODE::ADD_TILE;

        TileEditorMode(Editor* _editor): ApplicationMode(_editor) { }
        void on_enter() override;
        void on_exit() override;
        void update(float dt) override;
        void render() override;
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
        T& get_state()
        {
            std::type_index _index(typeid(T));
            if (m_mode_table.find(_index) != m_mode_table.end())
                return *static_cast<T*>(m_mode_table[_index].get());

            throw std::runtime_error("State type not found");
        }

        template<typename T>
        void set_initial_state()
        {
            std::type_index index(typeid(T));
            auto _it = m_mode_table.find(index);
            if (_it != m_mode_table.end())
            {
                m_current_mode = _it->second.get();
                m_current_mode->on_enter();
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
                    m_current_mode->on_exit();

                m_current_mode = _it->second.get();
                m_current_mode->on_enter();
            }
        }

        void update(float dt);
    private:
        ApplicationMode* m_current_mode = nullptr;
        std::unordered_map<std::type_index, std::unique_ptr<ApplicationMode>> m_mode_table;
    };
}
#endif

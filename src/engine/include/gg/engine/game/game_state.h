#ifndef _gg_engine_game_state_h_
#define _gg_engine_game_state_h_

#include "gg/core/debug/assert.h"
#include "gg/core/macro/macro.h"
#include "gg/engine/game/game_state_defs.h"

namespace gg::engine
{
    class game_state
    {
    public:

        // constructors

        game_state(void) noexcept;
        virtual ~game_state(void) noexcept = default;

        // methods

        void complete(completion_type type, uint32 param = k_no_param) noexcept
        {
            GG_ASSERT(completion_type::uncompleted != type);
            m_completion_param = param;
            m_completion_type = type;
        }

        void enter(void) noexcept
        {
            on_enter();
        }

        void leave(void) noexcept
        {
            on_leave();
        }

        void pause(void) noexcept
        {
            m_paused = true;
            on_pause();
        }

        void reset(void) noexcept
        {
            m_completion_param = k_no_param;
            m_completion_type = completion_type::uncompleted;
        }

        void resume(void) noexcept
        {
            on_resume();
            m_paused = false;
        }

        void update(float32 elapsed) noexcept;

        // methods

        uint32 get_completion_param(void) const noexcept
        {
            return m_completion_param;
        }

        completion_type get_completion_type(void) const noexcept
        {
            return m_completion_type;
        }

        // inquiries

        bool8 is_completed(void) const noexcept
        {
            return completion_type::uncompleted != m_completion_type;
        }

        bool8 is_paused(void) const noexcept
        {
            return m_paused;
        }

    private:

        // methods

        virtual void on_enter(void) noexcept
        {
        }

        virtual void on_leave(void) noexcept
        {
        }

        virtual void on_pause(void) noexcept
        {
        }

        virtual void on_resume(void) noexcept
        {
        }

        virtual void on_update(float32 GG_UNUSED_ARGUMENT(elapsed)) noexcept
        {
        }

    private:

        // attributes

        uint32 m_completion_param;
        completion_type m_completion_type;
        bool8 m_paused;
    };
}

#endif // _gg_engine_game_state_h_

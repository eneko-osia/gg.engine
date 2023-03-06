#ifndef _gg_engine_game_state_manager_h_
#define _gg_engine_game_state_manager_h_

#include "gg/core/container/map/hash_map.h"
#include "gg/engine/game/game_state.h"

namespace gg::engine
{
    class game_state_manager final
    {
    public:

        // constructors

        game_state_manager(void) noexcept;
        ~game_state_manager(void) noexcept;

        // methods

        void add(id_type state_id, game_state * state) noexcept;
        void add_navigation(
            completion_type type,
            id_type source,
            id_type destination,
            uint32 param = k_no_param) noexcept;
        void change(id_type destination) noexcept;
        void change_to_previous(void) noexcept;
        void pause(void) noexcept;
        void resume(void) noexcept;
        void update(float32 elapsed) noexcept;

    private:

        // type definitions

        typedef hash_map<id_type, id_type> navigation_map;
        typedef hash_map<id_type, game_state *> state_map;

        // methods

        void change(game_state * state) noexcept;
        void complete(completion_type type, id_type source, uint32 param) noexcept;
        uint32 get_navigation(completion_type type, id_type source, uint32 param) const noexcept;
        uint32 get_navigation_key(completion_type type, id_type source, uint32 param) const noexcept;

    private:

        // attributes

        navigation_map m_navigations;
        state_map m_states;
        game_state * m_current;
        game_state * m_previous;

    };
}

#endif // _gg_engine_game_state_manager_h_

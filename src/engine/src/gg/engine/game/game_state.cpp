#include "gg/engine/game/game_state.h"

//==============================================================================
namespace gg::engine
{
//==============================================================================

game_state::game_state(void) noexcept
    : m_completion_param(k_no_param)
    , m_completion_type(completion_type::uncompleted)
    , m_paused(false)
{
}

//==============================================================================

void game_state::update(float32 elapsed) noexcept
{
    if (!is_paused())
    {
        on_update(elapsed);
    }
}

//==============================================================================
}
//==============================================================================

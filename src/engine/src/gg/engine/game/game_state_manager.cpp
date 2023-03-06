#include "gg/engine/game/game_state_manager.h"

//==============================================================================

#include "gg/core/type/constant.h"

//==============================================================================
namespace gg::engine
{
//==============================================================================

game_state_manager::game_state_manager(void) noexcept
    : m_navigations()
    , m_states()
    , m_current(nullptr)
    , m_previous(nullptr)
{
}

game_state_manager::~game_state_manager(void) noexcept
{
    // for (auto * state : m_states)
    // {
    //     memory::delete(state);
    // }
}

//==============================================================================

void game_state_manager::add(id_type state_id, game_state * state) noexcept
{
    GG_RETURN_IF(!state);
    GG_RETURN_IF(m_states.has(state_id));
    m_states.insert(state_id, state);
}

void game_state_manager::add_navigation(
    completion_type type,
    id_type source,
    id_type destination,
    uint32 param) noexcept
{
    uint32 key = get_navigation_key(type, source, param);
    GG_RETURN_IF(m_navigations.has(key));
    m_navigations.insert(key, destination);
}

void game_state_manager::change(id_type destination) noexcept
{
    GG_ASSERT(k_id_type_invalid != destination);
    auto it = m_states.find(destination);
    game_state * state = (it != m_states.end()) ? it->second : nullptr;
    GG_ASSERT(state);
    change(state);
}

void game_state_manager::change(game_state * state) noexcept
{
    // set previous

    m_previous = m_current;

    // leave previous

    if (m_previous)
    {
        m_previous->leave();
    }

    // set current

    m_current = state;

    // enter current

    if (m_current)
    {
        m_current->enter();
    }
}

void game_state_manager::change_to_previous(void) noexcept
{
    change(m_previous);
}

void game_state_manager::complete(
    completion_type type,
    id_type source,
    uint32 param) noexcept
{
    change(get_navigation(type, source, param));
}

uint32 game_state_manager::get_navigation(
    completion_type type,
    id_type source,
    uint32 param) const noexcept
{
    uint32 navigation_key = get_navigation_key(type, source, param);
    auto cit = m_navigations.find(navigation_key);
    return (cit != m_navigations.end()) ? cit->second : k_id_type_invalid;
}

uint32 game_state_manager::get_navigation_key(completion_type type,
                                          id_type source,
                                          uint32 param) const noexcept
{
    // static ggcore::ref_string const separator = "-";

    // ggcore::static_string<256>	key;
    // ggcore::static_string<128>	param_as_string;
    // ggcore::static_string<128>	source_as_string;
    // ggcore::static_string<8>	type_as_string;

    // ggcore::converter::uitoa(param, param_as_string.get(), param_as_string.max_size());
    // ggcore::converter::uitoa(source, source_as_string.get(), source_as_string.max_size());
    // ggcore::converter::uitoa(cast(type), type_as_string.get(), type_as_string.max_size());

    // key.append(source_as_string);
    // key.append(separator);
    // key.append(type_as_string);
    // key.append(separator);
    // key.append(param_as_string);

    // return ggcrypt::hash::generate(key);
    GG_UNUSED(type);
    GG_UNUSED(source);
    return param;
}

void game_state_manager::pause(void) noexcept
{
    if (m_current)
    {
        m_current->pause();
    }
}

void game_state_manager::resume(void) noexcept
{
    if (m_current)
    {
        m_current->resume();
    }
}

void game_state_manager::update(float32 elapsed) noexcept
{
    if (m_current)
    {
        // update state
        m_current->update(elapsed);

        // check is complete
        if (m_current->is_completed())
        {
            // complete current state
            complete(m_current->get_completion_type(),
                     0, // m_current->get_id(),
                     m_current->get_completion_param());

            if (m_current)
            {
                // reset the completion parameters
                m_current->reset();
            }
        }
    }
}

//==============================================================================
}
//==============================================================================

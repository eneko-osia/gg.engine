#include "gg/engine/runtime/runtime_base.h"

//==============================================================================

#include "gg/log/channel/channel_helper.h"
#include "gg/log/log_manager.h"

//==============================================================================

GG_LOG_CHANNEL_CREATE(
    runtime,
    gg::log::flags::full,
    gg::log::level::normal,
    true);

//==============================================================================
namespace gg::engine
{
//==============================================================================

runtime_base::runtime_base(app::data const & data) noexcept
    : app::runtime(data)
    , m_modules()
    , m_exit_requested(false)
{
}

//==============================================================================

int32 runtime_base::main(void) noexcept
{
    if (!init())
    {
        finalize();
        return EXIT_FAILURE;
    }

    run();
    finalize();
    return EXIT_SUCCESS;
}

//==============================================================================
}
//==============================================================================

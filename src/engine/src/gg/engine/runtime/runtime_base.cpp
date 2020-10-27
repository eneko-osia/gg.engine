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
{
}

runtime_base::~runtime_base(void) noexcept
{
}

//==============================================================================

int32 runtime_base::main(void) noexcept
{
    if (init())
    {
        int32 result = run();
        finalize();
        return result;
    }

    return EXIT_FAILURE;
}

//==============================================================================
}
//==============================================================================

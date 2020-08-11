#include "gg/engine/runtime/runtime_base.h"

//==============================================================================

#include "gg/log/log_manager.h"

//==============================================================================
namespace gg::engine
{
//==============================================================================

runtime_base::runtime_base(app::data const & data) noexcept
    : app::runtime(data)
    , m_modules()
{
    log::log_manager::create();
}

runtime_base::~runtime_base(void) noexcept
{
    log::log_manager::destroy();
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

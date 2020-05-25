#include "gg/engine/runtime/runtime_base.h"

//==============================================================================
namespace gg
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

#include "gg/engine/gfx/gfx_module.h"

#include "gg/core/debug/assert.h"

//==============================================================================
namespace gg
{
//==============================================================================

void gfx_module::on_finalize(void) noexcept
{
}

bool8 gfx_module::on_init(void) noexcept
{
    #if defined(GG_OPENGL)
        GG_ASSERT_NOT_IMPLEMENTED();
    #endif

    #if defined(GG_VULKAN)
        GG_ASSERT_NOT_IMPLEMENTED();
    #endif

    return true;
}

//==============================================================================
}
//==============================================================================

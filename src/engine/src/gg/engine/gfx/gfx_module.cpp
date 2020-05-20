#include "gg/engine/gfx/gfx_module.h"

#include "gg/core/container/array/array_dynamic.h"
#include <iostream>

#if defined(GG_VULKAN)
#include "gg/engine/gfx/gfx_vulkan.h"
#endif

//==============================================================================
namespace gg
{
//==============================================================================
#if defined(GG_VULKAN)
static gg::gfx_vulkan s_vulkan;
#endif

void gfx_module::on_finalize(void) noexcept
{
#if defined(GG_VULKAN)
    s_vulkan.finalize();
#endif
}

bool8 gfx_module::on_init(void) noexcept
{
#if defined(GG_OPENGL)
    GG_ASSERT_NOT_IMPLEMENTED();
#endif

#if defined(GG_VULKAN)
    return s_vulkan.init();
#endif

    return true;
}

//==============================================================================
}
//==============================================================================

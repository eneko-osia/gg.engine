#if defined(GG_GFX)
//==============================================================================

#include "gg/engine/gfx/gfx_module.h"

//==============================================================================

#include "gg/core/macro/macro.h"
#include "gg/core/memory/memory.h"

#if defined(GG_OPENGL)
#include "gg/gfx/opengl/opengl_context.h"
#endif

#if defined(GG_VULKAN)
#include "gg/gfx/vulkan/vulkan_context.h"
#endif

//==============================================================================
namespace gg
{
//==============================================================================
gfx_module::gfx_module(void) noexcept
    : m_context(nullptr)
{
}

gfx_module::~gfx_module(void) noexcept
{
    memory::delete_object(m_context);
}

//==============================================================================

void gfx_module::on_finalize(void) noexcept
{
    m_context->finalize();
    memory::delete_object(m_context);
}

bool8 gfx_module::on_init(void) noexcept
{
#if defined(GG_OPENGL)
    m_context = memory::new_object<gfx::opengl_context>();
#elif defined(GG_VULKAN)
    m_context = memory::new_object<gfx::vulkan_context>();
#endif
    GG_RETURN_FALSE_IF_NULL(m_context);
    return m_context->init();
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================


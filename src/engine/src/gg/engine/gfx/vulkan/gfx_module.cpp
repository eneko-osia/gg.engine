#if defined(GG_APP_WINDOW_SUPPORT) && defined(GG_GFX_VULKAN_SUPPORT)
//==============================================================================

#include "gg/engine/gfx/vulkan/gfx_module.h"

//==============================================================================

#include "gg/core/memory/memory.h"
#include "gg/engine/runtime/runtime.h"
#include "gg/gfx/vulkan/vulkan_context_info.h"
#include "gg/gfx/vulkan/vulkan_context.h"

//==============================================================================
namespace gg::engine
{
//==============================================================================
gfx_vulkan_module::gfx_vulkan_module(void) noexcept
    : m_context(nullptr)
{
}

gfx_vulkan_module::~gfx_vulkan_module(void) noexcept
{
    GG_ASSERT(!m_context);
}

//==============================================================================

void gfx_vulkan_module::clear(void) noexcept
{
}

void gfx_vulkan_module::disable(void) noexcept
{
}

void gfx_vulkan_module::enable(void) noexcept
{
}

void gfx_vulkan_module::on_finalize(void) noexcept
{
    if (m_context)
    {
        m_context->finalize();
        memory::delete_object(m_context);
    }
}

bool8 gfx_vulkan_module::on_init(void) noexcept
{
    app::window * window = runtime::get_instance().get_window(0);
    GG_RETURN_FALSE_IF(!window);

    gfx::vulkan_context_info info;
    memory::zero(&info);

    m_context = memory::new_object<gfx::vulkan_context>();
    return m_context->init(window, &info);
}

void gfx_vulkan_module::render(void) noexcept
{
}

void gfx_vulkan_module::swap_buffer(void) noexcept
{
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================


#if defined(GG_GFX)
//==============================================================================

#include "gg/engine/gfx/gfx_module.h"

//==============================================================================

#include "gg/core/macro/macro.h"
#include "gg/core/memory/memory.h"
#include "gg/engine/runtime/runtime.h"

#if defined(GG_OPENGL)
    #include "gg/gfx/opengl/opengl_context_info.h"
    #include "gg/gfx/opengl/opengl_context.h"
#endif

#if defined(GG_VULKAN)
    #include "gg/gfx/vulkan/vulkan_context_info.h"
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
    GG_ASSERT_NULL(m_context);
}

//==============================================================================

void gfx_module::on_finalize(void) noexcept
{
    if (m_context)
    {
        m_context->finalize();
        memory::delete_object(m_context);
    }
}

bool8 gfx_module::on_init(void) noexcept
{
    app::window * window = runtime::get_instance().get_window(0);
    GG_RETURN_FALSE_IF_NULL(window);

#if defined(GG_OPENGL)

    gfx::opengl_context_info info;
    memory::zero(&info);
    info.m_red_size = 8;
    info.m_green_size = 8;
    info.m_blue_size = 8;
    info.m_alpha_size = 8;
    info.m_depth_size = 8;
    info.m_stencil_size = 8;
    info.m_full_screen = false;
    info.m_vsync_enabled = false;
    info.m_version_major = 3;
    info.m_version_minor = 0;
    m_context = memory::new_object<gfx::opengl_context>();
    return m_context->init(window, &info);

#elif defined(GG_VULKAN)

    gfx::vulkan_context_info info;
    memory::zero(&info);

    m_context = memory::new_object<gfx::vulkan_context>();
    return m_context->init(window, &info);

#else
    return false;
#endif
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================


#if defined(GG_GFX) && defined(GG_GFX_OPENGL_SUPPORT)
//==============================================================================

#include "gg/engine/gfx/opengl/gfx_opengl_module.h"

//==============================================================================

#include "gg/core/memory/memory.h"
#include "gg/engine/config/config_module.h"
#include "gg/engine/runtime/runtime.h"
#include "gg/gfx/opengl/context/opengl_context_info.h"
#include "gg/gfx/opengl/context/opengl_context.h"

// #if defined(GG_GFX_VULKAN_SUPPORT)
// #include "gg/gfx/vulkan/vulkan_context_info.h"
// #include "gg/gfx/vulkan/vulkan_context.h"
// #endif

//==============================================================================
namespace gg::engine
{
//==============================================================================
gfx_opengl_module::gfx_opengl_module(void) noexcept
    : m_context(nullptr)
{
}

gfx_opengl_module::~gfx_opengl_module(void) noexcept
{
    GG_ASSERT(!m_context);
}

//==============================================================================

void gfx_opengl_module::clear(void) noexcept
{
    m_context->enable();
    m_context->clear(255, 0, 0, 255);
}

void gfx_opengl_module::on_finalize(void) noexcept
{
    if (m_context)
    {
        m_context->finalize();
        memory::delete_object(m_context);
    }
}

bool8 gfx_opengl_module::on_init(void) noexcept
{
    app::window * window = runtime::get_instance().get_window(0);
    GG_RETURN_FALSE_IF(!window);

    config_module const * config =
        runtime::get_instance<runtime>().get_module<config_module>();

    gfx::opengl_context_info info;
    memory::zero(&info);
    info.m_red_size =
        config->get_value<uint8>(GG_TEXT("device/red_size"), 8);
    info.m_green_size =
        config->get_value<uint8>(GG_TEXT("device/green_size"), 8);
    info.m_blue_size =
        config->get_value<uint8>(GG_TEXT("device/blue_size"), 8);
    info.m_alpha_size =
        config->get_value<uint8>(GG_TEXT("device/alpha_size"), 8);
    info.m_depth_size =
        config->get_value<uint8>(GG_TEXT("device/depth_size"), 8);
    info.m_stencil_size =
        config->get_value<uint8>(GG_TEXT("device/stencil_size"), 8);
    info.m_full_screen =
        config->get_value<uint8>(GG_TEXT("device/full_screen"), false);
    info.m_vsync_enabled =
        config->get_value<uint8>(GG_TEXT("device/vsync_enabled"), false);
    info.m_version_major = 4;
    info.m_version_minor = 0;

    m_context = memory::new_object<gfx::opengl_context>();
    return m_context->init(window, &info);

// #if defined(GG_GFX_VULKAN_SUPPORT)
//     if (GG_TEXT("vulkan") == device_type)
//     {
//         gfx::vulkan_context_info info;
//         memory::zero(&info);

//         m_context = memory::new_object<gfx::vulkan_context>();
//         return m_context->init(window, &info);
//     }
// #endif
}

void gfx_opengl_module::render(void) noexcept
{
    // m_context->render();
}

void gfx_opengl_module::swap_buffer(void) noexcept
{
    m_context->swap_buffer();
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================


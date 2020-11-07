#if defined(GG_APP_WINDOW_SUPPORT) && defined(GG_GFX_OPENGL_SUPPORT)
//==============================================================================

#include "gg/engine/gfx/opengl/gfx_opengl_module.h"

//==============================================================================

#include "gg/app/window/window.h"
#include "gg/core/memory/memory.h"
#include "gg/engine/config/config_module.h"
#include "gg/engine/runtime/runtime.h"
#include "gg/gfx/opengl/context/opengl_context_info.h"
#include "gg/gfx/opengl/context/opengl_context.h"
#include "gg/gfx/opengl/viewport/opengl_viewport.h"

//==============================================================================
namespace gg::engine
{
//==============================================================================
gfx_opengl_module::gfx_opengl_module(void) noexcept
    : m_context(nullptr)
    , m_viewport(nullptr)
{
}

gfx_opengl_module::~gfx_opengl_module(void) noexcept
{
    GG_ASSERT(!m_viewport);
    GG_ASSERT(!m_context);
}

//==============================================================================

void gfx_opengl_module::clear(void) noexcept
{
    m_context->clear(255, 0, 0, 255);
}

void gfx_opengl_module::disable(void) noexcept
{
    m_context->disable();
}

void gfx_opengl_module::enable(void) noexcept
{
    m_context->enable();
}

void gfx_opengl_module::on_finalize(void) noexcept
{
    if (m_viewport)
    {
        m_viewport->finalize();
        memory::delete_object(m_viewport);
    }

    if (m_context)
    {
        m_context->finalize();
        memory::delete_object(m_context);
    }
}

bool8 gfx_opengl_module::on_init(void) noexcept
{
    static id_type const window_id = 0;
    app::window * window = runtime::get_instance().get_window(window_id);
    GG_RETURN_FALSE_IF(!window);

    config_module const * config =
        runtime::get_instance<runtime>().get_module<config_module>();
    GG_RETURN_FALSE_IF(!config);

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
    info.m_version_major =
        config->get_value<uint8>(GG_TEXT("device/opengl_version_major"), 4);
    info.m_version_minor =
        config->get_value<uint8>(GG_TEXT("device/opengl_version_minor"), 6);

    m_context = memory::new_object<gfx::opengl_context>();
    GG_RETURN_FALSE_IF(!m_context->init(window, &info));

    m_viewport = memory::new_object<gfx::opengl_viewport>();
    GG_RETURN_FALSE_IF(!m_viewport->init(window->get_width(), window->get_height()));

    return true;
}

void gfx_opengl_module::render(void) noexcept
{
    // m_renderer->render();
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


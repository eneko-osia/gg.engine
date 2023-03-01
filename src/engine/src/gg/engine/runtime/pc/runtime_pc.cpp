//==============================================================================
#if defined(GG_MAC) || defined(GG_LINUX) || defined(GG_WINDOWS)
//==============================================================================

#include "gg/engine/runtime/pc/runtime_pc.h"

//==============================================================================

#include "gg/app/debug/console/console.h"
#include "gg/core/system/lib/lib.h"
#include "gg/core/thread/thread.h"
#include "gg/engine/config/config_module.h"
#include "gg/engine/debug/debug_module.h"
#include "gg/engine/pattern/plugin/plugin.h"

#if defined(GG_APP_WINDOW_SUPPORT)
    #include "gg/app/window/window.h"
#endif // GG_APP_WINDOW_SUPPORT

#if defined(GG_GFX)
    #include "gg/engine/gfx/gfx_module.h"
    #include "gg/engine/gui/gui_module.h"
#if defined(GG_GFX_OPENGL_SUPPORT)
    #include "gg/engine/gfx/opengl/gfx_module.h"
#endif // GG_GFX_OPENGL_SUPPORT
#if defined(GG_GFX_VULKAN_SUPPORT)
    #include "gg/engine/gfx/vulkan/gfx_module.h"
#endif // GG_GFX_VULKAN_SUPPORT
#endif // GG_GFX

//==============================================================================
namespace gg::engine
{
//==============================================================================

runtime_pc::runtime_pc(app::data const & data) noexcept
    : runtime_base(data)
{
}

//==============================================================================

void runtime_pc::finalize(void) noexcept
{
#if defined(GG_APP_WINDOW_SUPPORT)
#if defined(GG_GFX)
    finalize_module<gui_module>();
    finalize_module<gfx_module>();
#endif // GG_GFX
    destroy_window(m_main_window_id);
#endif // GG_APP_WINDOW_SUPPORT

    finalize_module<config_module>();
#if defined(GG_DEBUG)
    finalize_module<debug_module>();
#endif // GG_DEBUG
}

bool8 runtime_pc::init(void) noexcept
{
#if defined(GG_DEBUG)
    GG_RETURN_FALSE_IF(!init_module<debug_module>());
#endif // GG_DEBUG
    GG_RETURN_FALSE_IF(!init_module<config_module>());

#if defined(GG_APP_WINDOW_SUPPORT)
    config_module * config = get_module<config_module>();
    m_main_window_id =
        create_window(
            config->get_value<string_ref>(GG_TEXT("engine/name"), GG_TEXT("gg::engine")),
            config->get_value<uint16>(GG_TEXT("engine/width"), 640),
            config->get_value<uint16>(GG_TEXT("engine/height"), 480));
    GG_RETURN_FALSE_IF(k_id_type_invalid == m_main_window_id);
    get_window(m_main_window_id)->add_observer(this);

#if defined(GG_GFX)
    string_ref device_type =
        config->get_value<string_ref>(GG_TEXT("device/type"), GG_TEXT("opengl"));
    if (GG_TEXT("opengl") == device_type)
    {
#if defined(GG_GFX_OPENGL_SUPPORT)
        GG_RETURN_FALSE_IF(!init_module<opengl::gfx_module>());
#endif
    }
    else if (GG_TEXT("vulkan") == device_type)
    {
#if defined(GG_GFX_VULKAN_SUPPORT)
        GG_RETURN_FALSE_IF(!init_module<gfx_vulkan_module>());
#endif
    }

    if (!has_module<gfx_module>())
    {
        log::logger::error<log::runtime>(GG_TEXT("%s device type is not supported"), device_type.c_str());
    }
    GG_RETURN_FALSE_IF(!init_module<gui_module>());
#endif // GG_GFX
#endif // GG_APP_WINDOW_SUPPORT

    lib game_lib;
    if (game_lib.load(GG_TEXT("game.dll")))
    {
        typedef plugin * (* create_plugin_f) (void);
        typedef void (* destroy_plugin_f) (plugin *);

        create_plugin_f create_plugin = game_lib.get_method<create_plugin_f>(GG_TEXT("create_plugin"));
        destroy_plugin_f destroy_plugin = game_lib.get_method<destroy_plugin_f>(GG_TEXT("destroy_plugin"));

        if (create_plugin && destroy_plugin)
        {
            plugin* plugin = create_plugin();
            if (plugin)
            {
                plugin->init();
                plugin->finalize();
                destroy_plugin(plugin);
            }
        }
        else
        {
            log::logger::error<log::runtime>(GG_TEXT("could not load create and destroy plugin methods from game_dll library"));
        }
    }
    else
    {
        log::logger::warning<log::runtime>(GG_TEXT("could not load game_dll library"));
    }

    return true;
}

void runtime_pc::on_close(void) noexcept
{
    request_exit();
}

void runtime_pc::on_gain_focus(void) noexcept
{
}

void runtime_pc::on_lost_focus(void) noexcept
{
}

void runtime_pc::run(void) noexcept
{
    #if defined(GG_APP_WINDOW_SUPPORT) && defined(GG_GFX)
    thread render_thread(
        [this] (void)
        {
            if (!this->has_module<gfx_module>() || !this->has_module<gui_module>())
            {
                return;
            }

            static gfx_module * const gfx = this->get_module<gfx_module>();
            static gui_module * const gui = this->get_module<gui_module>();

            gfx->enable();
            while (!this->is_exit_requested())
            {
                gfx->clear();
                gfx->render();
                gui->render();
                gfx->swap_buffer();
                thread::current::yield();
            }
            gfx->disable();
        });
    #endif

    thread simulation_thread(
        [this] (void)
        {
            while (!this->is_exit_requested())
            {
                // static animation_module * animation = get_animation_module();
                // static camera_module * camera = get_camera_module();
                // static screen_module * screen = get_screen_module();
                // static skeleton_module * skeleton = get_skeleton_module();
                // static world_module * world = get_world_module();

                // world_module->update(elapsed);
                // animation_module->update(elapsed);
                // skeleton_module->update(elapsed);
                // camera_module->update();
                // screen_module->update(elapsed);
                thread::current::yield();
            }
        });

    while (!this->is_exit_requested())
    {
        handle_messages();
        thread::current::yield();
    }

    #if defined(GG_APP_WINDOW_SUPPORT) && defined(GG_GFX)
    render_thread.join();
    #endif
    simulation_thread.join();
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================

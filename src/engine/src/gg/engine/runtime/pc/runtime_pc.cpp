#if defined(GG_MAC) || defined(GG_LINUX) || defined(GG_WINDOWS)
//==============================================================================

#include "gg/engine/runtime/pc/runtime_pc.h"

//==============================================================================

#include "gg/app/debug/console/console.h"
#include "gg/core/thread/thread.h"
#include "gg/engine/config/config_module.h"
#include "gg/engine/debug/debug_module.h"

#if defined(GG_APP_WINDOW_SUPPORT)
#include "gg/app/window/window.h"
#endif

#if defined(GG_GFX)
#include "gg/engine/gfx/gfx_module.h"
#include "gg/engine/gui/gui_module.h"
    #if defined(GG_GFX_OPENGL_SUPPORT)
    #include "gg/engine/gfx/opengl/gfx_opengl_module.h"
    #endif
    #if defined(GG_GFX_VULKAN_SUPPORT)
    #include "gg/engine/gfx/vulkan/gfx_vulkan_module.h"
    #endif
#endif

//==============================================================================
namespace gg::engine
{
//==============================================================================

runtime_pc::runtime_pc(app::data const & data) noexcept
    : runtime_base(data)
    , m_running(false)
{
}

//==============================================================================

void runtime_pc::finalize(void) noexcept
{
#if defined(GG_APP_WINDOW_SUPPORT) && defined(GG_GFX)
    finalize_module<gui_module>();
    finalize_module<gfx_module>();
#endif

    finalize_module<config_module>();

#if defined(GG_DEBUG)
    finalize_module<debug_module>();
#endif
}

bool8 runtime_pc::init(void) noexcept
{
#if defined(GG_DEBUG)
    GG_RETURN_FALSE_IF(!init_module<debug_module>());
#endif
    GG_RETURN_FALSE_IF(!init_module<config_module>());

#if defined(GG_APP_WINDOW_SUPPORT) && defined(GG_GFX)
    config_module * config = get_module<config_module>();
    id_type window_id =
        create_window(
            config->get_value<string_ref>(GG_TEXT("engine/name"), GG_TEXT("gg::engine")),
            config->get_value<uint16>(GG_TEXT("engine/width"), 640),
            config->get_value<uint16>(GG_TEXT("engine/height"), 480));
    GG_RETURN_FALSE_IF(id_type_invalid == window_id);
    get_window(window_id)->add_observer(this);

    string_ref device_type =
        config->get_value<string_ref>(GG_TEXT("device/type"), GG_TEXT("opengl"));
    if (GG_TEXT("opengl") == device_type)
    {
        #if defined(GG_GFX_OPENGL_SUPPORT)
        GG_RETURN_FALSE_IF(!init_module<gfx_opengl_module>());
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
#endif


    // HINSTANCE game_dll;
    // game_dll = LoadLibrary("game.dll");

    // if (game_dll != 0)
    // {
    //     printf("game_dll library loaded!\n");

    //     typedef int (__stdcall *funci_f)(void);
    //     typedef game * (__stdcall *game_create_f)(void);
    //     typedef void (__stdcall *game_destroy_f)(game *);

    //     funci_f funci = (funci_f ) GetProcAddress(game_dll, "funci");
    //     game_create_f game_create = (game_create_f ) GetProcAddress(game_dll, "game_create");
    //     game_destroy_f game_destroy = (game_destroy_f) GetProcAddress(game_dll, "game_destroy");

    //     if (game_create && game_destroy)
    //     {
    //         printf("methods loaded!\n");

    //         volatile int a = funci();

    //         if (a == 2)
    //         {
    //             game* game = game_create();
    //             // game->print();
    //             game_destroy(game);
    //             game = nullptr;
    //         }
    //     }
    //     else
    //     {
    //         printf("methods failed to load!\n");
    //     }
    // }
    // else
    // {
    //     printf("game_dll library failed to load!\n");
    // }

    return m_running = true;
}

void runtime_pc::on_close(void) noexcept
{
    m_running = false;
}

void runtime_pc::on_gain_focus(void) noexcept
{
}

void runtime_pc::on_lost_focus(void) noexcept
{
}

int32 runtime_pc::run(void) noexcept
{
    // thread simulation_thread(&render);
    // thread render_thread(&render);

#if defined(GG_APP_WINDOW_SUPPORT) && defined(GG_GFX)
    thread render_thread(
        [this] (void)
        {
            if (!this->has_module<gfx_module>())
            {
                return;
            }

            while (m_running)
            {
                static gfx_module * gfx = this->get_module<gfx_module>();
                static gui_module * gui = this->get_module<gui_module>();

                gfx->clear();
                gfx->render();
                // gui->render();
                gfx->swap_buffer();
                thread::current::yield();
            }
        });
#endif

    thread simulation_thread(
        [this] (void)
        {
            while (m_running)
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

    while (m_running)
    {
        handle_messages();
        thread::current::yield();
    }

#if defined(GG_APP_WINDOW_SUPPORT) && defined(GG_GFX)
    render_thread.join();
#endif
    simulation_thread.join();

    return EXIT_SUCCESS;
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================

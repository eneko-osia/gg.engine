#if defined(GG_MAC) || defined(GG_LINUX) || defined(GG_WINDOWS)
//==============================================================================

#include "gg/engine/runtime/pc/runtime_pc.h"

//==============================================================================

#include "gg/app/debug/console/console.h"
#include "gg/app/window/window.h"
#include "gg/core/thread/thread.h"
#include "gg/engine/config/config_module.h"
#include "gg/engine/debug/debug_module.h"

#if defined(GG_GFX)
#include "gg/engine/gfx/gfx_module.h"
#include "gg/engine/gui/gui_module.h"
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

    GG_RETURN_FALSE_IF(!init_module<gfx_module>());
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
    while (m_running)
    {
        handle_messages();
        thread::current::yield();
    }

    return EXIT_SUCCESS;
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================

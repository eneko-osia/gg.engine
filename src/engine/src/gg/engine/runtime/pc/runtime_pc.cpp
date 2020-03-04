#if defined(GG_MAC) || defined(GG_LINUX) || defined(GG_WINDOWS)
//==============================================================================

#include "gg/engine/runtime/pc/runtime_pc.h"

//==============================================================================

#include "gg/app/window/window.h"
#include "gg/core/string/macro/macro.h"
#include "gg/core/string/type/string_ref.h"
#include "gg/core/thread/thread.h"

//==============================================================================
namespace gg
{
//==============================================================================

runtime_pc::runtime_pc(data const & data) noexcept
    : runtime_base(data)
    , m_running(false)
{
}

//==============================================================================

void runtime_pc::finalize(void) noexcept
{
    window * win = get_window(1);
    win->remove_observer(this);
    destroy_window(1);
}

bool8 runtime_pc::init(void) noexcept
{
    window * win = create_window(1, string_ref(GG_TEXT("main")), 640, 480);
    GG_RETURN_FALSE_IF_NULL_ASSERT(win);
    win->add_observer(this);

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

void runtime_pc::on_quit(void) noexcept
{
    m_running = false;
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

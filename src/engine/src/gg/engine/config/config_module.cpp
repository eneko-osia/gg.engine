#include "gg/engine/config/config_module.h"

//==============================================================================

#include "gg/core/stream/file_istream.h"
#include "gg/engine/config/config_log.h"
#include "gg/log/logger.h"
#include "gg/log/channel/channel_helper.h"

//==============================================================================

GG_LOG_CHANNEL_CREATE(
    config,
    gg::log::flags::full,
    gg::log::level::normal,
    true);

//==============================================================================
namespace gg::engine
{
//==============================================================================

void config_module::on_finalize(void) noexcept
{
    m_configuration.unload();
}

bool8 config_module::on_init(void) noexcept
{
    array_dynamic<string_ref> files_to_load;
    files_to_load.emplace_back(GG_TEXT("data/config/engine.cfg"));

#if defined(GG_MAC)
    files_to_load.emplace_back(GG_TEXT("data/config/engine_mac.cfg"));
#elif defined(GG_LINUX)
    files_to_load.emplace_back(GG_TEXT("data/config/engine_linux.cfg"));
#elif defined(GG_WINDOWS)
    files_to_load.emplace_back(GG_TEXT("data/config/engine_windows.cfg"));
#endif

    files_to_load.emplace_back(GG_TEXT("data/config/game.cfg"));

#if defined(GG_MAC)
    files_to_load.emplace_back(GG_TEXT("data/config/game_mac.cfg"));
#elif defined(GG_LINUX)
    files_to_load.emplace_back(GG_TEXT("data/config/game_linux.cfg"));
#elif defined(GG_WINDOWS)
    files_to_load.emplace_back(GG_TEXT("data/config/game_windows.cfg"));
#endif

    bool8 loaded = true;
    container::for_each(
        files_to_load.begin(),
        files_to_load.end(),
        [&] (string_ref const & file_to_load)
        {
            file_istream file(file_to_load, stream_mode::text);
            if (file.is_valid())
            {
                if (!m_configuration.load(file))
                {
                    log::logger::warning<log::config>(
                        GG_TEXT("could not load %s file"),
                        file_to_load.c_str());
                    loaded = false;
                }
            }
            else
            {
                log::logger::verbose<log::config>(
                    GG_TEXT("file %s not found"),
                    file_to_load.c_str());
            }

        });
    return loaded;
}

//==============================================================================
}
//==============================================================================

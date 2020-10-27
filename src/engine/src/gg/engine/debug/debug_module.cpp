#include "gg/engine/debug/debug_module.h"

//==============================================================================

#include "gg/app/debug/console/console.h"
#include "gg/core/string/type/string_ref.h"
#include "gg/engine/runtime/runtime_log.h"
#include "gg/log/handler.h"
#include "gg/log/logger.h"

//==============================================================================
namespace gg::engine
{
//==============================================================================

class stdout_handler : public gg::log::handler
{
public:

    void log(log::level level, string_ref const & message) noexcept
    {
        GG_UNUSED(level);
        printf("%s\n", message.c_str());
    }
};

//==============================================================================

static stdout_handler s_handler;

//==============================================================================

void debug_module::on_finalize(void) noexcept
{
    log::log_manager::get_instance().remove_handler(&s_handler);
}

bool8 debug_module::on_init(void) noexcept
{
    GG_RETURN_FALSE_IF(!app::console::init(GG_TEXT("gg::engine::console")));
    log::log_manager::get_instance().add_handler(&s_handler);
    log::logger::normal<log::runtime>(
        GG_TEXT("%s initializing"),
        debug_module::get_name().c_str());
    return true;
}

//==============================================================================
}
//==============================================================================

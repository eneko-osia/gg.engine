#include "gg/engine/debug/debug_module.h"

//==============================================================================

#include "gg/app/debug/console/console.h"
#include "gg/core/string/type/string_ref.h"
#include "gg/log/log_manager.h"

//==============================================================================
namespace gg::engine
{
//==============================================================================

class stdout_handler : public gg::log::ilog_handler
{
public:

    void log(gg::log::level level, gg::string_ref const & message) noexcept
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
    return true;
}

//==============================================================================
}
//==============================================================================

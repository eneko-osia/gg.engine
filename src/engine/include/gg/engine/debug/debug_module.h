#ifndef _gg_engine_debug_module_h_
#define _gg_engine_debug_module_h_

#include "gg/engine/pattern/module/module.h"

namespace gg::engine
{
    class debug_module final : public module
    {
    public:

        GG_DECLARE_MODULE_ID(debug_module);

        // constructors

        debug_module(void) noexcept = default;
        ~debug_module(void) noexcept = default;

    private:

        // module override methods

        void on_finalize(void) noexcept override;
        bool8 on_init(void) noexcept override;
    };
}

#endif // _ggengine_debug_module_h_

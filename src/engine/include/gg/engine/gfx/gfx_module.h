#ifndef _gg_engine_gfx_module_h_
#define _gg_engine_gfx_module_h_

#include "gg/engine/pattern/module/module.h"

namespace gg::gfx { class context; }

namespace gg::engine
{
    class gfx_module final : public module
    {
    public:

        GG_DECLARE_MODULE_ID(gfx_module);

        // constructors

        gfx_module(void) noexcept;
        ~gfx_module(void) noexcept;

    private:

        // module override methods

        void on_finalize(void) noexcept override;
        bool8 on_init(void) noexcept override;

    private:

        // attributes

        gfx::context * m_context;
    };
}

#endif // _gg_engine_gfx_module_h_

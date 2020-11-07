#ifndef _gg_engine_gfx_module_h_
#define _gg_engine_gfx_module_h_

#include "gg/engine/pattern/module/module.h"

namespace gg::gfx { class context; }

namespace gg::engine
{
    class gfx_module : public module
    {
    public:

        GG_DECLARE_MODULE(gfx_module);

        // constructors

        gfx_module(void) noexcept = default;
        virtual ~gfx_module(void) noexcept = default;

        // virtual methods

        virtual void clear(void) noexcept = 0;
        virtual void disable(void) noexcept = 0;
        virtual void enable(void) noexcept = 0;
        virtual void render(void) noexcept = 0;
        virtual void swap_buffer(void) noexcept = 0;
    };
}

#endif // _gg_engine_gfx_module_h_

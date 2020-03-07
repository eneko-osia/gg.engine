#ifndef _gg_gfx_module_h_
#define _gg_gfx_module_h_

// include files

#include "gg/engine/pattern/module/module.h"

// namespace

namespace gg
{
    // class in charge of define a graphics module

    class gfx_module final : public module
    {
    public:

        // constructors

        gfx_module(void) noexcept = default;
        ~gfx_module(void) noexcept = default;

    private:

        // module override methods

        void on_finalize(void) noexcept override;
        bool8 on_init(void) noexcept override;
    };
}

#endif // _gg_gfx_module_h_

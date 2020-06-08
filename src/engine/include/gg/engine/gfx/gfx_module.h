#ifndef _gg_gfx_module_h_
#define _gg_gfx_module_h_

// include files

#include "gg/engine/pattern/module/module.h"

// namespace

namespace gg
{
    // forward declarations

    namespace gfx { class context; }

    // class in charge of define a graphics module

    class gfx_module final : public module
    {
    public:

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

#endif // _gg_gfx_module_h_

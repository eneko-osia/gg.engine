#ifndef _gg_gui_module_h_
#define _gg_gui_module_h_

// include files

#include "gg/engine/pattern/module/module.h"

// namespace

namespace gg::engine
{
    // class in charge of define a graphical user interface module

    class gui_module final : public module
    {
    public:

        GG_DECLARE_MODULE(gui_module);

        // constructors

        gui_module(void) noexcept = default;
        ~gui_module(void) noexcept = default;

    private:

        // module override methods

        void on_finalize(void) noexcept override;
        bool8 on_init(void) noexcept override;
    };
}

#endif // _gg_gui_module_h_

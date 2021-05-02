#ifndef _gg_engine_runtime_pc_h_
#define _gg_engine_runtime_pc_h_

#include "gg/app/window/iwindow_observer.h"
#include "gg/engine/runtime/runtime_base.h"

namespace gg::engine
{
    class runtime_pc : public runtime_base, public app::iwindow_observer
    {
    protected:

        // constructors

        runtime_pc(app::data const & data) noexcept;
        virtual ~runtime_pc(void) noexcept = default;

    private:

        // runtime_base override methods

        void finalize(void) noexcept override;
        bool8 init(void) noexcept override;
        void run(void) noexcept override;

        // iwindow_observer override methods

        void on_close(void) noexcept override;
        void on_gain_focus(void) noexcept override;
        void on_lost_focus(void) noexcept override;

        // attributes

        id_type m_main_window_id;
    };

    typedef class runtime_pc runtime_platform;
}

#endif // _gg_engine_runtime_pc_h_

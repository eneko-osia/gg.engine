#ifndef _gg_runtime_pc_h_
#define _gg_runtime_pc_h_

// include files

#include "gg/app/window/iwindow_observer.h"
#include "gg/engine/runtime/runtime_base.h"
#include <atomic>

// namespace

namespace gg::engine
{
    // type definitions

    typedef class runtime_pc runtime_platform;

    // class in charge of define a pc runtime

    class runtime_pc : public runtime_base, public app::iwindow_observer
    {
    protected:

        // constructors

        runtime_pc(app::data const & data) noexcept;
        virtual ~runtime_pc(void) noexcept = default;

    private:

        // runtime base override methods

        void finalize(void) noexcept override;
        bool8 init(void) noexcept override;
        int32 run(void) noexcept override;

        // window observer override methods

        void on_close(void) noexcept override;
        void on_gain_focus(void) noexcept override;
        void on_lost_focus(void) noexcept override;

    private:

        // attributes

        std::atomic<bool8> m_running;
    };
}

#endif // _gg_runtime_pc_h_

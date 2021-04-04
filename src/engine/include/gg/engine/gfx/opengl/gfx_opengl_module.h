#ifndef _gg_engine_gfx_opengl_module_h_
#define _gg_engine_gfx_opengl_module_h_

#include "gg/engine/gfx/gfx_module.h"
#include "gg/gfx/opengl/context/opengl_context.h"
#include "gg/gfx/opengl/viewport/opengl_viewport.h"

namespace gg::gfx
{
    class opengl_viewport;
}

namespace gg::engine
{
    class gfx_opengl_module final : public gfx_module
    {
    public:

        // constructors

        gfx_opengl_module(void) noexcept = default;
        ~gfx_opengl_module(void) noexcept = default;

    private:

        // module override methods

        void on_finalize(void) noexcept override;
        bool8 on_init(void) noexcept override;

        // gfx_module override methods

        void clear(void) noexcept override;
        void disable(void) noexcept override;
        void enable(void) noexcept override;
        void render(void) noexcept override;
        void swap_buffer(void) noexcept override;

    private:

        // attributes

        gfx::opengl_context m_context;
        gfx::opengl_viewport m_viewport;
    };
}

#endif // _gg_engine_gfx_opengl_module_h_

#ifndef _gg_engine_gfx_opengl_module_h_
#define _gg_engine_gfx_opengl_module_h_

#include "gg/engine/gfx/gfx_module.h"
#include "gg/gfx/opengl/context/opengl_context.h"
#include "gg/gfx/opengl/viewport/opengl_viewport.h"

namespace gg::engine::opengl
{
    class gfx_module final : public gg::engine::gfx_module
    {
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

        gfx::opengl::context m_context;
        gfx::opengl::viewport m_viewport;
    };
}

#endif // _gg_engine_gfx_opengl_module_h_

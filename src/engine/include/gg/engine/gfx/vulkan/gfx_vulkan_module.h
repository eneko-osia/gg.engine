#ifndef _gg_engine_gfx_vulkan_module_h_
#define _gg_engine_gfx_vulkan_module_h_

#include "gg/engine/gfx/gfx_module.h"

namespace gg::gfx { class vulkan_context; }

namespace gg::engine
{
    class gfx_vulkan_module final : public gfx_module
    {
    public:

        // constructors

        gfx_vulkan_module(void) noexcept;
        ~gfx_vulkan_module(void) noexcept;

    private:

        // module override methods

        void on_finalize(void) noexcept override;
        bool8 on_init(void) noexcept override;

        // methods

        void clear(void) noexcept override;
        void render(void) noexcept override;
        void swap_buffer(void) noexcept override;

    private:

        // attributes

        gfx::vulkan_context * m_context;
    };
}

#endif // _gg_engine_gfx_vulkan_module_h_

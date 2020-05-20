
#ifndef _gg_gfx_vulkan_h_
#define _gg_gfx_vulkan_h_

// include files

#include "gg/core/type/type.h"
#include <vulkan/vulkan.h>

// namespace

namespace gg
{
    // class in charge of define vulkan graphics

    class gfx_vulkan
    {
    public:

        // methods

        void finalize(void) noexcept;
        bool8 init(void) noexcept;

    private:

        VkInstance m_instance;
    };
}

#endif // _gg_gfx_vulkan_h_

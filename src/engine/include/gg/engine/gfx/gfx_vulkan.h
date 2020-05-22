
#ifndef _gg_gfx_vulkan_h_
#define _gg_gfx_vulkan_h_

// undefined previous definitions

#ifdef GG_VULKAN_VALIDATION_ENABLED
    #undef GG_VULKAN_VALIDATION_ENABLED
#endif

// define vulkan validation enabled

#if defined(GG_DEBUG)
    #define GG_VULKAN_VALIDATION_ENABLED 1
#else
    #define GG_VULKAN_VALIDATION_ENABLED 0
#endif

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

        // constructors

        gfx_vulkan(void) noexcept;
        ~gfx_vulkan(void) noexcept = default;

        // methods

        void finalize(void) noexcept;
        bool8 init(void) noexcept;

    private:

        VkPhysicalDevice m_device;
        VkInstance m_instance;

    #if GG_VULKAN_VALIDATION_ENABLED
        VkDebugUtilsMessengerEXT m_messenger;
    #endif
    };
}

#endif // _gg_gfx_vulkan_h_

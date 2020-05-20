#if defined(GG_VULKAN)
//==============================================================================

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

//==============================================================================

#include "gg/engine/gfx/gfx_vulkan.h"

//==============================================================================

#include "gg/core/container/array/array_dynamic.h"
#include "gg/core/container/array/array_static.h"

//==============================================================================
namespace gg
{
//==============================================================================

static void get_required_extensions(array_dynamic<char8 const *> & extensions)
{
#if GG_VULKAN_VALIDATION_ENABLED
    extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif
}

static void get_supported_extensions(array_dynamic<char8 const *> & extensions)
{
    // uint32 num_properties = 0;
    // vkEnumerateInstanceExtensionProperties(nullptr, &num_properties, nullptr);

    // array_dynamic<VkExtensionProperties> properties;
    // properties.resize(num_properties);
    // vkEnumerateInstanceExtensionProperties(nullptr, &num_properties, properties.data());

    // for (VkExtensionProperties const & property : properties)
    // {
    //     extensions.emplace_back(property.extensionName);
    // }
}

#if GG_VULKAN_VALIDATION_ENABLED
static bool has_validation_support(array_dynamic<char8 const *> const & validations)
{
    static constexpr uint32 k_max_layers = 64;

    uint32 num_layers = 0;
    vkEnumerateInstanceLayerProperties(&num_layers, nullptr);
    GG_RETURN_FALSE_IF_TRUE(num_layers > k_max_layers);

    array_static<VkLayerProperties, k_max_layers> layers;
    vkEnumerateInstanceLayerProperties(&num_layers, layers.data());

    for (char8 const * layer_name : validations)
    {
        bool found = false;

        for (uint32 i = 0; i < num_layers; ++i)
        {
            if (string::compare(layer_name, layers[i].layerName) == 0)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            return false;
        }
    }

    return true;
}
#endif

#if GG_VULKAN_VALIDATION_ENABLED
static VKAPI_ATTR VkBool32
VKAPI_CALL log_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT severity,
    VkDebugUtilsMessageTypeFlagsEXT type,
    const VkDebugUtilsMessengerCallbackDataEXT* data,
    void* user_data)
{
    printf("Validation layer: %s\n", data->pMessage);
    return VK_FALSE;
}
#endif

//==============================================================================

void gfx_vulkan::finalize(void) noexcept
{
#if GG_VULKAN_VALIDATION_ENABLED
    // auto vkDestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(m_instance, "vkDestroyDebugUtilsMessengerEXT");
    // GG_RETURN_FALSE_IF_NULL(vkDestroyDebugUtilsMessengerEXT);
    // vkDestroyDebugUtilsMessengerEXT(m_instance, debug_handle, nullptr);
#endif

    vkDestroyInstance(m_instance, nullptr);
}

bool8 gfx_vulkan::init(void) noexcept
{
#if GG_VULKAN_VALIDATION_ENABLED
    array_dynamic<char8 const *> validation;
    validation.emplace_back("VK_LAYER_KHRONOS_validation");
    GG_RETURN_FALSE_IF_FALSE(has_validation_support(validation));
#endif

    VkApplicationInfo app_info = {};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName = "GG Engine";
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName = "GG Engine";
    app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.apiVersion = VK_API_VERSION_1_0;

    array_dynamic<char8 const *> extensions;
    get_required_extensions(extensions);

#if GG_VULKAN_VALIDATION_ENABLED
    VkDebugUtilsMessengerCreateInfoEXT debug_info = {};
    debug_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    debug_info.messageSeverity =
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    debug_info.messageType =
        VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    debug_info.pfnUserCallback = log_callback;
    debug_info.pUserData = nullptr;
#endif

    VkInstanceCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pApplicationInfo = &app_info;
    create_info.enabledExtensionCount = extensions.size();
    create_info.ppEnabledExtensionNames = extensions.data();

#if GG_VULKAN_VALIDATION_ENABLED
    create_info.enabledLayerCount = validation.size();
    create_info.ppEnabledLayerNames = validation.data();
    create_info.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debug_info;
#else
    create_info.enabledLayerCount = 0;
    create_info.ppEnabledLayerNames = nullptr;
    create_info.pNext = nullptr;
#endif

    VkResult result = vkCreateInstance(&create_info, nullptr, &m_instance);

#if GG_VULKAN_VALIDATION_ENABLED
    VkDebugUtilsMessengerEXT debug_handle = {};
    auto vkCreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(m_instance, "vkCreateDebugUtilsMessengerEXT");
    GG_RETURN_FALSE_IF_NULL(vkCreateDebugUtilsMessengerEXT);
    vkCreateDebugUtilsMessengerEXT(m_instance, &debug_info, nullptr, &debug_handle);
#endif

    return VK_SUCCESS == result;
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================

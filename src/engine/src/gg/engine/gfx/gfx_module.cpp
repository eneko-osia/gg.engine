#include "gg/engine/gfx/gfx_module.h"

#include "gg/core/container/array/array_dynamic.h"
#include <iostream>

#if defined(GG_VULKAN)
#include <vulkan/vulkan.h>
#endif

//==============================================================================
namespace gg
{
//==============================================================================

#if defined(GG_VULKAN)

bool has_support(array_dynamic<char8 const *> const & validations)
{
    uint32 num_layers = 0;
    vkEnumerateInstanceLayerProperties(&num_layers, nullptr);

    array_dynamic<VkLayerProperties> layers;
    layers.resize(num_layers);

    vkEnumerateInstanceLayerProperties(&num_layers, layers.data());

    for (char8 const * layer_name : validations)
    {
        bool found = false;

        for (VkLayerProperties const & layer : layers)
        {
            if (string::compare(layer_name, layer.layerName) == 0)
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

//==============================================================================

void gfx_module::on_finalize(void) noexcept
{
}

bool8 gfx_module::on_init(void) noexcept
{
#if defined(GG_OPENGL)
    GG_ASSERT_NOT_IMPLEMENTED();
#endif

#if defined(GG_VULKAN)

    array_dynamic<char8 const *> validation;
    validation.emplace_back("VK_LAYER_KHRONOS_validation");

#if defined(GG_DEBUG)
    constexpr bool enable_validation = true;
#else
    constexpr bool enable_validation = false;
#endif

    if (!enable_validation || (enable_validation && has_support(validation)))
    {
        VkInstance instance;

        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "GG Engine";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        // uint32 extensionCount = 0;
        // vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        // array_dynamic<VkExtensionProperties> extensions; extensions.resize(extensionCount);
        // vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        VkInstanceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = 0;
        createInfo.ppEnabledExtensionNames = nullptr;

        if (enable_validation)
        {
            createInfo.enabledLayerCount = validation.size();
            createInfo.ppEnabledLayerNames = validation.data();
        }
        else
        {
            createInfo.enabledLayerCount = 0;
        }

        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
        vkDestroyInstance(instance, nullptr);
    }
#endif

    return true;
}

//==============================================================================
}
//==============================================================================

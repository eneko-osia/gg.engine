#===============================================================================

find_package(Vulkan REQUIRED)
if(NOT Vulkan_FOUND)
    message(FATAL_ERROR "Vulkan could not be found")
endif()

#===============================================================================

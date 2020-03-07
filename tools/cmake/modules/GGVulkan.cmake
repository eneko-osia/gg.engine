#===============================================================================

find_package(Vulkan REQUIRED)
if(Vulkan_FOUND)
    if(NOT "vulkan" IN_LIST gfx)
        list(APPEND gfx "vulkan")
        set(gfx ${gfx} CACHE INTERNAL "Graphic libraries" FORCE)
    endif()
else()
    message(FATAL_ERROR "Vulkan could not be found")
endif()

#===============================================================================

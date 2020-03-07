#===============================================================================

find_package(OpenGL REQUIRED)
if(OpenGL_FOUND)
    if(NOT "opengl" IN_LIST gfx)
        list(APPEND gfx "opengl")
        set(gfx ${gfx} CACHE INTERNAL "Graphic libraries" FORCE)
    endif()
else()
    message(FATAL_ERROR "OpenGL could not be found")
endif()

#===============================================================================

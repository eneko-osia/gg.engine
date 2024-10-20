#===============================================================================

find_package(OpenGL REQUIRED)
if(NOT OpenGL_FOUND)
    message(FATAL_ERROR "OpenGL could not be found")
endif()

#===============================================================================

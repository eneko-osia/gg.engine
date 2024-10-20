#===============================================================================

if(UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    if(NOT X11_FOUND)
        message(FATAL_ERROR "X11 could not be found")
    endif()
endif()

#===============================================================================

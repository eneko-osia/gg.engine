#===============================================================================

if(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    set(COMPILER "clang")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(COMPILER "clang")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(COMPILER "gnu")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(COMPILER "msvc")
else()
    message(FATAL_ERROR "Unsuported c++ compiler [${CMAKE_CXX_COMPILER_ID}]")
endif()

#===============================================================================

if(CMAKE_SYSTEM_NAME STREQUAL "Android")
    set(SYSTEM "android")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(SYSTEM "mac")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(SYSTEM "linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(SYSTEM "windows")
elseif(CMAKE_SYSTEM_NAME STREQUAL "WindowsStore")
    set(SYSTEM "uwp")
else()
    message(FATAL_ERROR "Unsuported build system [${CMAKE_SYSTEM_NAME}]")
endif()

#===============================================================================

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(SYSTEM_ARCHITECTURE "x86_64")
else()
    set(SYSTEM_ARCHITECTURE "x86")
endif()

#===============================================================================

set(CMAKE_CONFIGURATION_TYPES "debug" "release_with_debug" "release"
    CACHE STRING "Build configuration types" FORCE
)
mark_as_advanced(CMAKE_CONFIGURATION_TYPES)

#===============================================================================

set(CMAKE_C_FLAGS_RELEASE_WITH_DEBUG ${CMAKE_C_FLAGS_RELWITHDEBINFO}
    CACHE STRING "c release with debug compiler flags"
)
mark_as_advanced(CMAKE_C_FLAGS_RELEASE_WITH_DEBUG)

set(CMAKE_CXX_FLAGS_RELEASE_WITH_DEBUG ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}
    CACHE STRING "cxx release with debug compiler flags"
)
mark_as_advanced(CMAKE_CXX_FLAGS_RELEASE_WITH_DEBUG)

set(CMAKE_EXE_LINKER_FLAGS_RELEASE_WITH_DEBUG ${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO}
    CACHE STRING "cxx release with debug linker flags"
)
mark_as_advanced(CMAKE_EXE_LINKER_FLAGS_RELEASE_WITH_DEBUG)

set(CMAKE_MODULE_LINKER_FLAGS_RELEASE_WITH_DEBUG ${CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO}
    CACHE STRING "cxx release with debug module linker flags"
)
mark_as_advanced(CMAKE_MODULE_LINKER_FLAGS_RELEASE_WITH_DEBUG)

set(CMAKE_SHARED_LINKER_FLAGS_RELEASE_WITH_DEBUG ${CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO}
    CACHE STRING "cxx release with debug shared linker flags"
)
mark_as_advanced(CMAKE_SHARED_LINKER_FLAGS_RELEASE_WITH_DEBUG)

set(CMAKE_STATIC_LINKER_FLAGS_RELEASE_WITH_DEBUG ${CMAKE_STATIC_LINKER_FLAGS_RELWITHDEBINFO}
    CACHE STRING "cxx release with debug static linker flags"
)
mark_as_advanced(CMAKE_STATIC_LINKER_FLAGS_RELEASE_WITH_DEBUG)

#===============================================================================

foreach(CONFIGURATION ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${CONFIGURATION} CONFIGURATION_UPPER)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIGURATION_UPPER}
        "${CMAKE_BINARY_DIR}/lib/${SYSTEM}/${SYSTEM_ARCHITECTURE}/${CONFIGURATION}"
        CACHE STRING "Archive output directory [${CONFIGURATION}]"
    )
    mark_as_advanced(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIGURATION_UPPER})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONFIGURATION_UPPER}
        "${CMAKE_BINARY_DIR}/lib/${SYSTEM}/${SYSTEM_ARCHITECTURE}/${CONFIGURATION}"
        CACHE STRING "Library output directory [${CONFIGURATION}]"
    )
    mark_as_advanced(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONFIGURATION_UPPER})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIGURATION_UPPER}
        "${CMAKE_BINARY_DIR}/bin/${SYSTEM}/${SYSTEM_ARCHITECTURE}/${CONFIGURATION}"
        CACHE STRING "Runtime output directory [${CONFIGURATION}]"
    )
    mark_as_advanced(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIGURATION_UPPER})
endforeach()

#===============================================================================

set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES})
if(NOT(CMAKE_BUILD_TYPE STREQUAL "debug" OR
       CMAKE_BUILD_TYPE STREQUAL "release_with_debug" OR
       CMAKE_BUILD_TYPE STREQUAL "release"))
    set(CMAKE_BUILD_TYPE "debug" CACHE STRING "Build type [${CMAKE_CONFIGURATION_TYPES}]" FORCE)
endif()

#===============================================================================


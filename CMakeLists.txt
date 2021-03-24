# cmake version check
cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

# project
project(gg.engine VERSION 0.0.1 LANGUAGES CXX)

# options
option(GG_CORE                  "" ON)
option(GG_TEST                  "" ON)
option(GG_LOG                   "" ON)
option(GG_APP                   "" ON)
option(GG_APP_WINDOW_SUPPORT    "" ON)
option(GG_CRYPT                 "" ON)
option(GG_CONFIG                "" ON)
option(GG_GFX                   "" ON)
option(GG_GFX_OPENGL_SUPPORT    "" ON)
option(GG_GFX_VULKAN_SUPPORT    "" ON)

option(GGLIBS_ENABLE_DOC        "" OFF)
option(GGLIBS_ENABLE_TESTING    "" ON)

# add gg.libs
add_subdirectory("deps/gg.libs")

# modules path
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake/modules
    CACHE INTERNAL
    "CMake module path"
    FORCE
)

# includes
include(CMakeDependentOption)
include(GGFunctions)
include(GGPython)

# options
CMAKE_DEPENDENT_OPTION(
    GGENGINE_ENABLE_TESTING
    "enable tests"
    ON
    GG_TEST
    OFF
)

# testing
if(GGENGINE_ENABLE_TESTING)
    # enable testing
    enable_testing()

    # include catch test parser
    include(catch/Catch)
endif()

# add engine
add_subdirectory("src/engine")

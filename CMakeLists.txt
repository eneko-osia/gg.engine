# cmake version check
cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

# project
project(gg.engine VERSION 0.0.1 LANGUAGES CXX)

# includes
include(CMakeDependentOption)

# options
option(
    GG_ENGINE_CLIENT
    "client build mode"
    OFF
)

option(
    GG_ENGINE_SERVER
    "server build mode"
    OFF
)

option(
    GG_ENGINE_ENABLE_TESTING
    "enable tests"
    OFF
)

if(GG_ENGINE_CLIENT)
    message(STATUS "Configuring client build mode")
elseif(GG_ENGINE_SERVER)
    message(STATUS "Configuring server build mode")
else()
    message(FATAL_ERROR "Build mode is undefined [GG_ENGINE_CLIENT | GG_ENGINE_SERVER]")
endif()

option(GG_CORE                  "" ON)
option(GG_APP                   "" ON)
option(GG_LOG                   "" ON)
option(GG_CONFIG                "" ON)

# dependent options
cmake_dependent_option(
    GG_APP_WINDOW_SUPPORT
    "app window support"
    ON
    GG_ENGINE_CLIENT
    OFF
)

cmake_dependent_option(
    GG_GFX
    "gfx library"
    ON
    GG_ENGINE_CLIENT
    OFF
)

cmake_dependent_option(
    GG_GFX_OPENGL_SUPPORT
    "gfx opengl library"
    ON
    GG_ENGINE_CLIENT
    OFF
)

cmake_dependent_option(
    GG_GFX_VULKAN_SUPPORT
    "gfx vulkan library"
    ON
    GG_ENGINE_CLIENT
    OFF
)

cmake_dependent_option(
    GG_GUI
    "gui library"
    OFF
    GG_ENGINE_CLIENT
    OFF
)

cmake_dependent_option(
    GG_TEST
    "enable tests"
    ON
    GG_ENGINE_ENABLE_TESTING
    OFF
)

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
include(GGFunctions)

# testing
if(GG_ENGINE_ENABLE_TESTING)
    # enable testing
    enable_testing()

    # include catch test parser
    include(catch/Catch)
endif()

# add engine
add_subdirectory("src/engine")

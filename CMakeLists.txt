# cmake version check
cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

# project
project(gg.engine VERSION 0.0.1 LANGUAGES CXX)

# options 
option(GG_CORE              "" ON)
option(GG_TEST              "" ON)
option(GG_APP               "" ON)
option(GG_CRYPT             "" OFF)
option(GG_CONFIG            "" OFF)

option(GGLIBS_ENABLE_DOC        "" OFF)
option(GGLIBS_ENABLE_TESTING    "" OFF)

# add gg.libs
add_subdirectory("deps/gg.libs")

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
    include(catch/ParseAndAddCatchTests)
endif()

# add engine
add_subdirectory("src/engine")

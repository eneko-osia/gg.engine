# cmake version check
cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

# project
project(gg.engine VERSION 0.0.1 LANGUAGES CXX)

# options
option(GG_CORE              "" ON)
option(GG_TEST              "" OFF)
option(GG_APP               "" ON)
option(GG_CRYPT             "" OFF)
option(GG_CONFIG            "" OFF)

option(GG_ENABLE_DOC        "" OFF)
option(GG_ENABLE_TESTING    "" OFF)

# add gg.libs
add_subdirectory("deps/gg.libs")

# includes
include(GGPython)

# add engine
add_subdirectory("src/engine")
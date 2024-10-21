# cmake version check
cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

# project
project(gg.engine VERSION 0.0.1 LANGUAGES C CXX)

# check that we are not building on the source directory
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(
        FATAL_ERROR
        "Please do not build in a source directory (or any directory with CMakeLists.txt file) and use a build subdirectory. "
        "Please remove CMakeCache.txt and CMakeFiles"
    )
endif()

# directories
set(DOC_DIRECTORY   "${CMAKE_CURRENT_SOURCE_DIR}/doc")
set(SRC_DIRECTORY   "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(TOOLS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tools")

# modules path
set(CMAKE_MODULE_PATH "${TOOLS_DIRECTORY}/cmake/modules" ${CMAKE_MODULE_PATH})

# includes
include(CMakeDependentOption)
include(GGFunctions)
include(GGSystem)

# options
option(GG_ENABLE_DOC     "enable documentation" ON)
option(GG_ENABLE_TESTING "enable tests"         ON)

# configure version file
configure_file(
    "${TOOLS_DIRECTORY}/cmake/version/version.h.in"
    "${SRC_DIRECTORY}/engine/include/gg/version.h"
)

# set global properties
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# documentation
if (GG_ENABLE_DOC)
    # includes
    include(GGDoxygen)

    # add documentaion source directories
    set(DOXYGEN_SRC_DIRECTORY "${SRC_DIRECTORY}/engine")

    # configure doxyfile
    configure_file(
        "${TOOLS_DIRECTORY}/cmake/doxygen/doxyfile.in"
        "${DOC_DIRECTORY}/doxyfile"
    )

    # add doc target
    add_custom_target(
        gg.docs
        COMMAND ${DOXYGEN_EXECUTABLE} "${DOC_DIRECTORY}/doxyfile"
        WORKING_DIRECTORY ${DOC_DIRECTORY}
        COMMENT "Generating documentation..."
        VERBATIM
    )

    # group folder
    set_target_properties(gg.docs PROPERTIES FOLDER gg.libs.docs)
endif()

# testing
if(GG_ENABLE_TESTING)
    # enable testing
    enable_testing()

    # include catch test parser
    include(catch/Catch)

    # add test
    add_subdirectory("${SRC_DIRECTORY}/test")
endif()

# add engine
add_subdirectory("${SRC_DIRECTORY}/engine")

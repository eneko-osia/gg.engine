# generate src files
generate_src_files(${CMAKE_CURRENT_SOURCE_DIR})

# include source files
include(GGSrcFiles.cmake)

# library
add_library(
    gg.test
    STATIC
        ${INCLUDE_FILES}
        ${SRC_FILES}
)

# include directories
target_include_directories(
    gg.test
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/deps"
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# compile features
target_compile_features(
    gg.test
    PUBLIC
        cxx_std_17
)

# compile options
target_compile_options(
    gg.test
    PRIVATE
        # clang
        $<$<STREQUAL:${COMPILER},clang>:-fexceptions>
        $<$<STREQUAL:${COMPILER},clang>:-Wall>
        $<$<STREQUAL:${COMPILER},clang>:-Werror>
        $<$<STREQUAL:${COMPILER},clang>:-Wextra>
        $<$<STREQUAL:${COMPILER},clang>:-Wpedantic>
        # gnu
        $<$<STREQUAL:${COMPILER},gnu>:-fexceptions>
        $<$<STREQUAL:${COMPILER},gnu>:-Wall>
        $<$<STREQUAL:${COMPILER},gnu>:-Werror>
        $<$<STREQUAL:${COMPILER},gnu>:-Wextra>
        $<$<STREQUAL:${COMPILER},gnu>:-Wpedantic>
        # msvc
        $<$<STREQUAL:${COMPILER},msvc>:/EHsc>
        $<$<STREQUAL:${COMPILER},msvc>:/W4>
        $<$<STREQUAL:${COMPILER},msvc>:/WX>
)

# group folder
set_target_properties(gg.test PROPERTIES FOLDER gg.test)

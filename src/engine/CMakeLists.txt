# generate src files
generate_src_files(${CMAKE_CURRENT_SOURCE_DIR})

# includes
include(GGThreads)

# include source files
include(GGSrcFiles.cmake)

# library
add_library(
    gg.engine
    STATIC
        ${INCLUDE_FILES}
        ${SRC_FILES}
)

# include directories
target_include_directories(
    gg.engine
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# compile features
target_compile_features(
    gg.engine
    PUBLIC
        cxx_std_17
)

# compile definitions
target_compile_definitions(
    gg.engine
    PUBLIC
        $<$<CONFIG:debug>:GG_DEBUG>
        $<$<CONFIG:release_with_debug>:GG_DEBUG>
        $<$<STREQUAL:${COMPILER},clang>:GG_CLANG>
        $<$<STREQUAL:${COMPILER},gnu>:GG_GNU>
        $<$<STREQUAL:${COMPILER},msvc>:GG_MSVC>
        $<$<STREQUAL:${SYSTEM},android>:GG_ANDROID>
        $<$<STREQUAL:${SYSTEM},linux>:GG_LINUX>
        $<$<STREQUAL:${SYSTEM},mac>:GG_MAC>
        $<$<STREQUAL:${SYSTEM},uwp>:GG_UWP>
        $<$<STREQUAL:${SYSTEM},windows>:GG_WINDOWS>
        $<$<STREQUAL:${SYSTEM_ARCHITECTURE},x86>:GG_X86>
        $<$<STREQUAL:${SYSTEM_ARCHITECTURE},x86_64>:GG_X86_64>
    PRIVATE
        $<$<STREQUAL:${COMPILER},msvc>:_CRT_SECURE_NO_WARNINGS>
        $<$<STREQUAL:${COMPILER},msvc>:_HAS_EXCEPTIONS=0>
)

# compile options
target_compile_options(
    gg.engine
    PRIVATE
        # clang
        $<$<STREQUAL:${COMPILER},clang>:-fno-exceptions>
        $<$<STREQUAL:${COMPILER},clang>:-Wall>
        $<$<STREQUAL:${COMPILER},clang>:-Werror>
        $<$<STREQUAL:${COMPILER},clang>:-Wextra>
        $<$<STREQUAL:${COMPILER},clang>:-Wno-format-security>
        $<$<STREQUAL:${COMPILER},clang>:-Wno-nonnull>
        $<$<STREQUAL:${COMPILER},clang>:-Wpedantic>
        # gnu
        $<$<STREQUAL:${COMPILER},gnu>:-fno-exceptions>
        $<$<STREQUAL:${COMPILER},gnu>:-Wall>
        $<$<STREQUAL:${COMPILER},gnu>:-Werror>
        $<$<STREQUAL:${COMPILER},gnu>:-Wextra>
        $<$<STREQUAL:${COMPILER},gnu>:-Wno-format-security>
        $<$<STREQUAL:${COMPILER},gnu>:-Wno-nonnull>
        $<$<STREQUAL:${COMPILER},gnu>:-Wpedantic>
        # msvc
        # $<$<STREQUAL:${COMPILER},msvc>:/EHs-c->
        $<$<STREQUAL:${COMPILER},msvc>:/W4>
        $<$<STREQUAL:${COMPILER},msvc>:/WX>
)

# link libraries
target_link_libraries(
    gg.engine
    PRIVATE
        Threads::Threads
        ${CMAKE_DL_LIBS}
)

# group folder
set_target_properties(gg.engine PROPERTIES FOLDER gg.engine)

# testing
if(GG_ENABLE_TESTING)
    # executable
    add_executable(gg.engine.test ${TEST_FILES})

    # include directories
    target_include_directories(
        gg.engine.test
        PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}/test"
    )

    # compile options
    target_compile_options(
        gg.engine.test
        PRIVATE
            # clang
            $<$<STREQUAL:${COMPILER},clang>:-fexceptions>
            $<$<STREQUAL:${COMPILER},clang>:-Wall>
            $<$<STREQUAL:${COMPILER},clang>:-Werror>
            $<$<STREQUAL:${COMPILER},clang>:-Wextra>
            $<$<STREQUAL:${COMPILER},clang>:-Wno-format-security>
            $<$<STREQUAL:${COMPILER},clang>:-Wno-nonnull>
            $<$<STREQUAL:${COMPILER},clang>:-Wpedantic>
            # gnu
            $<$<STREQUAL:${COMPILER},gnu>:-fexceptions>
            $<$<STREQUAL:${COMPILER},gnu>:-Wall>
            $<$<STREQUAL:${COMPILER},gnu>:-Werror>
            $<$<STREQUAL:${COMPILER},gnu>:-Wextra>
            $<$<STREQUAL:${COMPILER},gnu>:-Wno-format-security>
            $<$<STREQUAL:${COMPILER},gnu>:-Wno-nonnull>
            $<$<STREQUAL:${COMPILER},gnu>:-Wpedantic>
            # msvc
            $<$<STREQUAL:${COMPILER},msvc>:/EHsc>
            $<$<STREQUAL:${COMPILER},msvc>:/W4>
            $<$<STREQUAL:${COMPILER},msvc>:/WX>
    )

    # link libraries
    target_link_libraries(
        gg.engine.test
        PRIVATE
            gg.engine
            gg.test
    )

    # group folder
    set_target_properties(gg.engine.test PROPERTIES FOLDER gg.engine.test)

    # parse tests
    catch_discover_tests(gg.engine.test)
endif()

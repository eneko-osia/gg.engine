# generate src files
generate_src_files(${CMAKE_CURRENT_SOURCE_DIR})

# includes
include(GGSrcFiles.cmake)

# library
add_library(
    gg.engine
    STATIC
        ${include_files}
        ${src_files}
)

# include directories
target_include_directories(
    gg.engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# compile definitions
target_compile_definitions(
    gg.engine
    PUBLIC
        GG_ENGINE
    PRIVATE
        $<$<STREQUAL:${compiler},msvc>:_HAS_EXCEPTIONS=0>
)

# compile options
target_compile_options(
    gg.engine
    PRIVATE
        $<$<STREQUAL:${compiler},gnu>:-fno-exceptions>
        $<$<STREQUAL:${compiler},gnu>:-Wall>
        $<$<STREQUAL:${compiler},gnu>:-Wextra>
        $<$<STREQUAL:${compiler},gnu>:-Wpedantic>
        $<$<STREQUAL:${compiler},gnu>:-Werror>
        #$<$<STREQUAL:${compiler},msvc>:/EHs-c->
        $<$<STREQUAL:${compiler},msvc>:/W4>
        $<$<STREQUAL:${compiler},msvc>:/WX>
)

# link libraries
target_link_libraries(
    gg.engine
    PUBLIC
        gg.config
        gg.app
        gg.log
        gg.core
)

if(GG_ENGINE_CLIENT)
    target_link_libraries(
        gg.engine
        PUBLIC
            # gg.gui
            gg.gfx
    )
endif()

# group folder
set_target_properties(gg.engine PROPERTIES FOLDER gg.engine)

# testing
if(GG_ENGINE_ENABLE_TESTING)
    # executable
    add_executable(gg.engine.test ${test_files})

    # include directories
    target_include_directories(
        gg.engine.test
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/test
    )

    # compile options
    target_compile_options(
        gg.engine.test
        PRIVATE
            $<$<STREQUAL:${compiler},gnu>:-fexceptions>
            $<$<STREQUAL:${compiler},gnu>:-Wall>
            $<$<STREQUAL:${compiler},gnu>:-Wextra>
            $<$<STREQUAL:${compiler},gnu>:-Wpedantic>
            $<$<STREQUAL:${compiler},gnu>:-Werror>
            $<$<STREQUAL:${compiler},msvc>:/EHsc>
            $<$<STREQUAL:${compiler},msvc>:/W4>
            $<$<STREQUAL:${compiler},msvc>:/WX>
    )

    # link libraries
    target_link_libraries(gg.engine.test gg.test gg.engine)

    # group folder
    set_target_properties(gg.engine.test PROPERTIES FOLDER gg.engine.test)

    # parse tests
    catch_discover_tests(gg.engine.test)
endif()

# executable files
set(executable_files
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gg/engine/runtime/runtime_bin.cxx
)
create_groups(${CMAKE_CURRENT_SOURCE_DIR} "${executable_files}")

if(GG_ENGINE_CLIENT)
    set(executable_name "gg.engine.client")
else(GG_ENGINE_SERVER)
    set(executable_name "gg.engine.server")
endif()

# executable
if(platform STREQUAL "windows")
    add_executable(
        ${executable_name}
        WIN32
            ${executable_files}
    )
else()
    add_executable(
        ${executable_name}
            ${executable_files}
    )
endif()

# link libraries
target_link_libraries(${executable_name} gg.engine)

# group folder
set_target_properties(${executable_name} PROPERTIES FOLDER gg.engine)

# rename executable
# set_target_properties(${executable_name} PROPERTIES OUTPUT_NAME gg.engine)

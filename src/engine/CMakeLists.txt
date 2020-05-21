# generate src files
generate_src_files(${CMAKE_CURRENT_SOURCE_DIR})

# includes
if(GGENGINE_OPENGL)
    include(GGOpenGL)
endif()

if(GGENGINE_VULKAN)
    include(GGVulkan)
endif()

include(GGSrcFiles.cmake)

# library
add_library(
    gg.engine
    STATIC
        ${deps_files}
        ${include_files}
        ${src_files}
)

# include directories
target_include_directories(
    gg.engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/deps
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if(GGENGINE_OPENGL)
    target_include_directories(
        gg.engine
        PRIVATE
            ${OPENGL_INCLUDE_DIR}
    )
endif()

if(GGENGINE_VULKAN)
    target_include_directories(
        gg.engine
        PRIVATE
            ${Vulkan_INCLUDE_DIRS}
    )
endif()

# compile definitions
target_compile_definitions(
    gg.engine
    PUBLIC
        GG_ENGINE
        $<$<IN_LIST:opengl,${gfx}>:GG_OPENGL>
        $<$<IN_LIST:vulkan,${gfx}>:GG_VULKAN>
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
        #$<$<STREQUAL:${compiler},msvc>:/EHs-c->
        #$<$<STREQUAL:${compiler},msvc>:/W4>
        $<$<STREQUAL:${compiler},msvc>:/WX>
)

# link libraries
target_link_libraries(
    gg.engine
    gg.app
    $<$<IN_LIST:opengl,${gfx}>:${OPENGL_LIBRARIES}>
    $<$<IN_LIST:vulkan,${gfx}>:${Vulkan_LIBRARIES}>
)

# group folder
set_target_properties(gg.engine PROPERTIES FOLDER gg.engine)

# testing
if(GGENGINE_ENABLE_TESTING)
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
            $<$<STREQUAL:${compiler},msvc>:/EHsc>
            #$<$<STREQUAL:${compiler},msvc>:/W4>
            $<$<STREQUAL:${compiler},msvc>:/WX>
    )

    # link libraries
    target_link_libraries(gg.engine.test gg.test gg.engine)

    # group folder
    set_target_properties(gg.engine.test PROPERTIES FOLDER gg.engine.test)

    # parse tests
    ParseAndAddCatchTests(gg.engine.test)
endif()

# executable files
set(executable_files
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gg/engine/runtime/runtime_bin.cxx
)
create_groups(${CMAKE_CURRENT_SOURCE_DIR} "${executable_files}")

# executable
if(platform STREQUAL "windows")
    add_executable(
        gg.engine-bin
        WIN32
            ${executable_files}
    )
else()
    add_executable(
        gg.engine-bin
            ${executable_files}
    )
endif()

# link libraries
target_link_libraries(gg.engine-bin gg.engine)

# group folder
set_target_properties(gg.engine-bin PROPERTIES FOLDER gg.engine)

# rename executable
set_target_properties(gg.engine-bin PROPERTIES OUTPUT_NAME gg.engine)

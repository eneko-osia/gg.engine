# generate src files
generate_src_files(${CMAKE_CURRENT_SOURCE_DIR})

# includes
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

# compile definitions
target_compile_definitions(
    gg.engine
    PUBLIC
        GG_engine
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
target_link_libraries(gg.engine gg.app)

# group folder
set_target_properties(gg.engine PROPERTIES FOLDER gg.libs)

# executable
if(platform STREQUAL "windows")
    add_executable(
        gg.engine-bin
        WIN32
            ${include_files}
            ${src_files}
    )
else()
    add_executable(
        gg.engine-bin
            ${include_files}
            ${src_files}
    )
endif()

# link libraries
target_link_libraries(gg.engine-bin gg.engine)

# group folder
set_target_properties(gg.engine-bin PROPERTIES FOLDER gg.engine)

# rename executable
set_target_properties(gg.engine-bin PROPERTIES OUTPUT_NAME gg.engine)

#===============================================================================

function(create_groups BASE_DIR FILES_TO_GROUP)
    foreach(FILE_TO_GROUP IN LISTS FILES_TO_GROUP)
        get_filename_component(FILE_DIRECTORY "${FILE_TO_GROUP}" DIRECTORY)
        string(REPLACE "${BASE_DIR}" "" GROUP "${FILE_DIRECTORY}")
        string(REPLACE "/" "\\" GROUP "${GROUP}")
        source_group("${GROUP}" FILES "${FILE_TO_GROUP}")
    endforeach()
endfunction()

#===============================================================================

function(generate_src_files BASE_DIR)
    set(FILENAME "${BASE_DIR}/GGSrcFiles.cmake")
    file(WRITE "${FILENAME}" "# @generated - run cmake configure to generate this file\n\n")

    list(APPEND INCLUDE_FILE_EXTENSIONS "h" "hpp")
    list(APPEND SRC_FILE_EXTENSIONS "h" "hpp" "c" "cpp")
    write_files_in_folder(${FILENAME} ${BASE_DIR} "include" "${INCLUDE_FILE_EXTENSIONS}")
    write_files_in_folder(${FILENAME} ${BASE_DIR} "src" "${SRC_FILE_EXTENSIONS}")
    write_files_in_folder(${FILENAME} ${BASE_DIR} "test" "${SRC_FILE_EXTENSIONS}")

    file(APPEND "${FILENAME}" "# groups\n")
    file(APPEND "${FILENAME}" "create_groups(\${CMAKE_CURRENT_SOURCE_DIR} \"\${INCLUDE_FILES}\")\n")
    file(APPEND "${FILENAME}" "create_groups(\${CMAKE_CURRENT_SOURCE_DIR} \"\${SRC_FILES}\")\n")
    file(APPEND "${FILENAME}" "create_groups(\${CMAKE_CURRENT_SOURCE_DIR} \"\${TEST_FILES}\")\n")
endfunction()

#===============================================================================

function(write_files_in_folder FILENAME BASE_DIR DIRECTORY EXTENSIONS)
    foreach(EXTENSION ${EXTENSIONS})
        list(APPEND GLOBBING_EXPRESSIONS "${BASE_DIR}/${DIRECTORY}/*.${EXTENSION}")
    endforeach()

    file(GLOB_RECURSE FILES ${GLOBBING_EXPRESSIONS})
    if(NOT FILES STREQUAL "")
        string(TOUPPER ${DIRECTORY} DIRECTORY_UPPER)
        file(APPEND "${FILENAME}" "# ${DIRECTORY} files\n")
        file(APPEND "${FILENAME}" "set(${DIRECTORY_UPPER}_FILES\n")
        foreach(FILE ${FILES})
            string(REPLACE "${BASE_DIR}" "\${CMAKE_CURRENT_SOURCE_DIR}" FILE "${FILE}")
            file(APPEND "${FILENAME}" "    \"${FILE}\"\n")
        endforeach()
        file(APPEND "${FILENAME}" ")\n")
    endif()
endfunction()

#===============================================================================

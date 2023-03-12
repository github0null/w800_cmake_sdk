
# Auto add subdirectory
file(GLOB sub_files RELATIVE "${CMAKE_CURRENT_LIST_DIR}" "${CMAKE_CURRENT_LIST_DIR}/*")
foreach(file_name ${sub_files})
    if(IS_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/${file_name}")
        if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/${file_name}/CMakeLists.txt")
            message(STATUS "add_subdirectory: ${CMAKE_CURRENT_LIST_DIR}/${file_name}")
            add_subdirectory("${file_name}")
        endif()
    endif()
endforeach()

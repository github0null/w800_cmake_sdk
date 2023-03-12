
set(MODULE_NAME app)

set(SUB_MODULES)

# Auto add subdirectory
file(GLOB sub_files RELATIVE "${CMAKE_CURRENT_LIST_DIR}" "${CMAKE_CURRENT_LIST_DIR}/*")
foreach(file_name ${sub_files})
    if(IS_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/${file_name}")
        if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/${file_name}/CMakeLists.txt")
            list(APPEND SUB_MODULES "${file_name}")
        endif()
    endif()
endforeach()

if(CONFIG_W800_USE_NIMBLE)
    list(REMOVE_ITEM SUB_MODULES "btapp")
else()
    list(REMOVE_ITEM SUB_MODULES "bleapp")
endif()

set(OBJS)

foreach(name ${SUB_MODULES})
    list(APPEND OBJS "$<TARGET_OBJECTS:${name}>")
endforeach()

add_library(${MODULE_NAME} INTERFACE)

foreach(name ${SUB_MODULES})
    message(STATUS "add_subdirectory: ${CMAKE_CURRENT_LIST_DIR}/${name}")
    add_subdirectory("${name}")
    target_link_libraries(${MODULE_NAME} INTERFACE "${name}")
endforeach()


get_filename_component(MODULE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(C_SRCS)
set(ASM_SRCS)

file(GLOB_RECURSE C_SRCS LIST_DIRECTORIES false RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "*.c")

list(REMOVE_ITEM C_SRCS
    "fsdata_lwip.c"
    "fsdata_lwip_basic.c"
    "fsdata_lwip_ruigong.c"
    "fsdata_lwip_russian.c")

add_library(${MODULE_NAME} STATIC
    ${C_SRCS}
    ${ASM_SRCS})

target_include_directories(${MODULE_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(${MODULE_NAME} PRIVATE
    )


get_filename_component(MODULE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(C_SRCS)
set(ASM_SRCS)

file(GLOB_RECURSE C_SRCS LIST_DIRECTORIES false RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" 
    "easylogger/src/*.c"
    "easylogger/port/*.c")

add_library(${MODULE_NAME} STATIC
    ${C_SRCS}
    ${ASM_SRCS})

target_include_directories(${MODULE_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/easylogger/inc)

target_compile_definitions(${MODULE_NAME} PRIVATE
    )


set(MODULE_NAME wmsys)

set(SRCS)

file(GLOB_RECURSE SRCS LIST_DIRECTORIES false RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "*.c"
    "*.S")

add_library(${MODULE_NAME} STATIC
    ${SRCS})

target_include_directories(${MODULE_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(${MODULE_NAME} PRIVATE
    )


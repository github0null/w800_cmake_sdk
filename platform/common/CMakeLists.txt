
set(MODULE_NAME wmcommon)

set(SRCS)

file(GLOB SRCS LIST_DIRECTORIES false RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "crypto/*.c"
    "fwup/*.c"
    "mem/*.c"
    "params/*.c"
    "task/*.c"
    "utils/*.c")

add_library(${MODULE_NAME} STATIC
    ${SRCS})

target_include_directories(${MODULE_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(${MODULE_NAME} PRIVATE
    )

target_compile_options(${MODULE_NAME} PRIVATE
    "-Wno-unused-variable"
    "-Wno-unused-but-set-variable")
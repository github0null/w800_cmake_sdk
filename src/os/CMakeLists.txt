
get_filename_component(MODULE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(SRCS)

file(GLOB SRCS LIST_DIRECTORIES false RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "rtos/*.c"
    "rtos/source/*.c"
    "rtos/ports/xt804/*.c"
    "rtos/ports/xt804/*.S")

add_library(${MODULE_NAME} STATIC
    ${SRCS})

target_include_directories(${MODULE_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/rtos/include)

target_compile_definitions(${MODULE_NAME} PRIVATE
    )

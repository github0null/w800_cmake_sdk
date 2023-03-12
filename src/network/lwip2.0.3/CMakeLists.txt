
get_filename_component(MODULE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

include(Filelists.cmake)

set(C_SRCS)

file(GLOB C_SRCS LIST_DIRECTORIES false RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "*.c")

list(APPEND C_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/netif/wm_ethernet.c
    ${CMAKE_CURRENT_SOURCE_DIR}/netif/ethernetif.c
    ${CMAKE_CURRENT_SOURCE_DIR}/core/alg.c)

add_library(${MODULE_NAME} STATIC
    ${C_SRCS}
    ${LWIPNOAPPSFILES})

target_include_directories(${MODULE_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_definitions(${MODULE_NAME} PRIVATE
    )

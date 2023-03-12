
get_filename_component(MODULE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(C_SRCS)
set(ASM_SRCS)

file(GLOB_RECURSE C_SRCS LIST_DIRECTORIES false RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "*.c")

list(REMOVE_ITEM C_SRCS 
    "address.c"
    "async.c"
    "block.c"
    "coap_io.c"
    "coap_io_lwip.c"
    "coap_time.c"
    "debug.c"
    "encode.c"
    "hashkey.c"
    "mem_libcoap.c"
    "net.c"
    "option.c"
    "pdu.c"
    "resource.c"
    "sr.c"
    "subscribe.c"
    "uri_libcoap.c")

add_library(${MODULE_NAME} STATIC
    ${C_SRCS}
    ${ASM_SRCS})

target_include_directories(${MODULE_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_definitions(${MODULE_NAME} PRIVATE
    )

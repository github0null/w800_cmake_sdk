
get_filename_component(MODULE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(C_SRCS)
set(ASM_SRCS)

file(GLOB_RECURSE C_SRCS LIST_DIRECTORIES false RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "*.c")

list(REMOVE_ITEM C_SRCS
    "minihuf.c"
    "minilex.c"
    "rewrite.c"
    "server.c"
    "server-handshake.c"
    "sha-1.c"
    "smtp.c"
    "ssl-http2.c"
    "ssl-server.c"
    "alloc.c"
    "daemonize.c"
    "extension.c"
    "extension-permessage-deflate.c"
    "getifaddrs.c"
    "hpack.c"
    "http2.c"
    "lejp.c"
    "lejp-conf.c"
    "libev.c"
    "libuv.c"
    "lws-plat-mbed3.c")

add_library(${MODULE_NAME} STATIC
    ${C_SRCS}
    ${ASM_SRCS})

target_include_directories(${MODULE_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(${MODULE_NAME} PRIVATE
    )

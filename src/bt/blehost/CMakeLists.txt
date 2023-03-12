
set(MODULE_NAME blehost)

set(C_SRCS)

file(GLOB C_SRCS LIST_DIRECTORIES false RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "*.c"
    "ext/tinycrypt/src/*.c"
    "nimble/host/mesh/src/*.c"
    "nimble/host/services/gap/src/*.c"
    "nimble/host/services/gatt/src/*.c"
    "nimble/host/src/*.c"
    "nimble/host/store/config/src/*.c"
    "nimble/host/store/ram/src/*.c"
    "nimble/host/utils/src/*.c"
    "nimble/transport/uart/src/*.c"
    "porting/w800/src/*.c")

add_library(${MODULE_NAME} STATIC
    ${C_SRCS})

target_include_directories(${MODULE_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/nimble/host/include
    ${CMAKE_CURRENT_SOURCE_DIR}/nimble/host/mesh/include
    ${CMAKE_CURRENT_SOURCE_DIR}/nimble/host/services/gap/include
    ${CMAKE_CURRENT_SOURCE_DIR}/nimble/host/services/gatt/include
    ${CMAKE_CURRENT_SOURCE_DIR}/nimble/host/config/include
    ${CMAKE_CURRENT_SOURCE_DIR}/nimble/host/ram/include
    ${CMAKE_CURRENT_SOURCE_DIR}/nimble/host/util/include
    ${CMAKE_CURRENT_SOURCE_DIR}/nimble/include
    ${CMAKE_CURRENT_SOURCE_DIR}/nimble/transport/uart/include
    ${CMAKE_CURRENT_SOURCE_DIR}/porting/w800/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ext/tinycrypt/include
    ${CMAKE_CURRENT_SOURCE_DIR}/nimble/host/store/config/include
    ${CMAKE_CURRENT_SOURCE_DIR}/nimble/host/store/ram/include)

target_compile_definitions(${MODULE_NAME} PRIVATE
    )


set(MODULE_NAME bthost)

set(C_SRCS)

file(GLOB_RECURSE C_SRCS LIST_DIRECTORIES false RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "*.c")

add_library(${MODULE_NAME} STATIC
    ${C_SRCS})

target_include_directories(${MODULE_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/main
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/stack
    ${CMAKE_CURRENT_SOURCE_DIR}/stack/include
    ${CMAKE_CURRENT_SOURCE_DIR}/gki/wm
    ${CMAKE_CURRENT_SOURCE_DIR}/gki/common
    ${CMAKE_CURRENT_SOURCE_DIR}/vnd/include
    ${CMAKE_CURRENT_SOURCE_DIR}/bta/include
    ${CMAKE_CURRENT_SOURCE_DIR}/osi/include
    ${CMAKE_CURRENT_SOURCE_DIR}/hci/include
    ${CMAKE_CURRENT_SOURCE_DIR}/btif/include
    ${CMAKE_CURRENT_SOURCE_DIR}/embdrv/sbc/encoder/include
    ${CMAKE_CURRENT_SOURCE_DIR}/embdrv/sbc/decoder/include
    ${CMAKE_CURRENT_SOURCE_DIR}/btcore/include)

target_compile_definitions(${MODULE_NAME} PRIVATE
    )


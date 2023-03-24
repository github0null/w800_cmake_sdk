
set(MODULE_NAME "w800sdk")

# ref: https://github.com/github0null/cmake_embedded_project_rules
include(${CMAKE_SOURCE_DIR}/cmake/utils/kconfig.cmake)

if(NOT DEFINED W800_SDK_CONF_PATH)
    set(W800_SDK_CONF_PATH "${CMAKE_CURRENT_LIST_DIR}/sdk.conf")
endif()

message(STATUS "use w800 sdk config: ${W800_SDK_CONF_PATH}")

if(NOT EXISTS "${W800_SDK_CONF_PATH}")
    message(FATAL_ERROR "not found config file: '${W800_SDK_CONF_PATH}'")
endif()

kconfig_include("${W800_SDK_CONF_PATH}"
    OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    OUTPUT_HEADER_NAME "w800sdk_conf.h"
    OUTPUT_CONF_NAME "w800sdk_conf")

set(W800_PRIVATE_LIBS
    wlan
    btcontroller
    dsp)

set(W800_TARGET_LIBS 
    app
    wmarch
    wmcommon
    drivers
    network
    os
    wmsys
    blehost)

if(CONFIG_W800_FIRMWARE_DEBUG)
    add_compile_definitions(WM_SWD_ENABLE=1)
endif()

add_library(${MODULE_NAME} STATIC 
    ${CMAKE_CURRENT_LIST_DIR}/w800sdk.c)

target_link_directories(${MODULE_NAME} PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/lib/w800)

target_link_libraries(${MODULE_NAME} PUBLIC 
    -Wl,--whole-archive ${W800_PRIVATE_LIBS} ${W800_TARGET_LIBS} -Wl,--no-whole-archive)

# gen signature pubkey into C header
if(CONFIG_W800_IMAGE_SIGN)
    if((NOT EXISTS "${PROJECT_SOURCE_DIR}/${CONFIG_W800_IMAGE_SIGN_PUBKEY_PATH}") OR ("${CONFIG_W800_IMAGE_SIGN_PUBKEY_PATH}" STREQUAL ""))
        set(CONFIG_W800_IMAGE_SIGN_PUBKEY_PATH "${CMAKE_CURRENT_LIST_DIR}/tools/w800/ca/capub.pem")
    endif()
    message(STATUS "firmware signature pubkey: '${CONFIG_W800_IMAGE_SIGN_PUBKEY_PATH}'")
    file(READ "${CONFIG_W800_IMAGE_SIGN_PUBKEY_PATH}" _sign_pubkey_txt)
    string(REPLACE "\n" ";" _sign_pubkey_lines ${_sign_pubkey_txt})
    list(FILTER _sign_pubkey_lines EXCLUDE REGEX "^-+BEGIN.*")
    list(FILTER _sign_pubkey_lines EXCLUDE REGEX "^-+END.*")
    list(FILTER _sign_pubkey_lines EXCLUDE REGEX "[ ]+")
    list(JOIN _sign_pubkey_lines "" _sign_pubkey_base64_string)
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/w800sdk_pubkey_sign.h" "#define W800SDK_PUBKEY_SIGN_BASE64 \"${_sign_pubkey_base64_string}\"")
endif()

set(EXPORT_INC_DIRS)
set(EXPORT_GCC_FLGS)
set(EXPORT_GCC_DEFS)

list(APPEND EXPORT_INC_DIRS
    # sdk_cfg
    ${CMAKE_CURRENT_BINARY_DIR}
    # base
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/include/app
    ${CMAKE_CURRENT_LIST_DIR}/include/arch/xt804
    ${CMAKE_CURRENT_LIST_DIR}/include/arch/xt804/csi_core
    ${CMAKE_CURRENT_LIST_DIR}/include/arch/xt804/csi_dsp
    ${CMAKE_CURRENT_LIST_DIR}/include/driver
    ${CMAKE_CURRENT_LIST_DIR}/include/net
    ${CMAKE_CURRENT_LIST_DIR}/include/os
    ${CMAKE_CURRENT_LIST_DIR}/include/platform
    ${CMAKE_CURRENT_LIST_DIR}/include/wifi
    ${CMAKE_CURRENT_LIST_DIR}/include/bt
    # platform
    ${CMAKE_CURRENT_LIST_DIR}/platform/common/params
    ${CMAKE_CURRENT_LIST_DIR}/platform/inc
    ${CMAKE_CURRENT_LIST_DIR}/platform/sys
    # components
    ${CMAKE_CURRENT_LIST_DIR}/src/app/bleapp
    ${CMAKE_CURRENT_LIST_DIR}/src/app/easylogger/easylogger/inc
    ${CMAKE_CURRENT_LIST_DIR}/src/app/lwrb-2.0.3/lwrb/src/include/lwrb
    ${CMAKE_CURRENT_LIST_DIR}/src/app/wm_atcmd
    ${CMAKE_CURRENT_LIST_DIR}/src/app/dhcpserver
    ${CMAKE_CURRENT_LIST_DIR}/src/app/dnsserver
    ${CMAKE_CURRENT_LIST_DIR}/src/app/web
    ${CMAKE_CURRENT_LIST_DIR}/src/app/cloud
    ${CMAKE_CURRENT_LIST_DIR}/src/app/cJSON
    ${CMAKE_CURRENT_LIST_DIR}/src/app/rmms
    ${CMAKE_CURRENT_LIST_DIR}/src/app/ntp
    ${CMAKE_CURRENT_LIST_DIR}/src/app/httpclient
    ${CMAKE_CURRENT_LIST_DIR}/src/app/oneshotconfig
    ${CMAKE_CURRENT_LIST_DIR}/src/app/iperf
    ${CMAKE_CURRENT_LIST_DIR}/src/app/mqtt
    ${CMAKE_CURRENT_LIST_DIR}/src/app/ping
    ${CMAKE_CURRENT_LIST_DIR}/src/app/polarssl/include
    ${CMAKE_CURRENT_LIST_DIR}/src/app/mDNS/mDNSPosix
    ${CMAKE_CURRENT_LIST_DIR}/src/app/mDNS/mDNSCore
    ${CMAKE_CURRENT_LIST_DIR}/src/app/ota
    ${CMAKE_CURRENT_LIST_DIR}/src/app/libwebsockets-2.1-stable
    ${CMAKE_CURRENT_LIST_DIR}/src/app/fatfs
    ${CMAKE_CURRENT_LIST_DIR}/src/app/mbedtls/include
    ${CMAKE_CURRENT_LIST_DIR}/src/app/mbedtls/ports
    ${CMAKE_CURRENT_LIST_DIR}/src/network/api2.0.3
    ${CMAKE_CURRENT_LIST_DIR}/src/network/lwip2.0.3/include
    ${CMAKE_CURRENT_LIST_DIR}/src/os/rtos/include
    ${CMAKE_CURRENT_LIST_DIR}/src/app/factorycmd)

list(APPEND EXPORT_GCC_FLGS
    "-std=gnu99"
    "-Wall")

list(APPEND EXPORT_GCC_DEFS
    "TLS_CONFIG_CPU_XT804=1"
    "GCC_COMPILE=1"
    "NIMBLE_FTR=1")

# export
target_include_directories(${MODULE_NAME} PUBLIC ${EXPORT_INC_DIRS})
target_compile_definitions(${MODULE_NAME} PUBLIC ${EXPORT_GCC_DEFS})
target_compile_options(${MODULE_NAME} PUBLIC ${EXPORT_GCC_FLGS})

# only for current target
include_directories(${EXPORT_INC_DIRS})
add_compile_definitions(${EXPORT_GCC_DEFS})
add_compile_options(${EXPORT_GCC_FLGS} 
    "-Wno-implicit-function-declaration" 
    "-Wno-unused-function"
    "-Wno-unused-variable"
    "-Wno-unused-but-set-variable"
    "-Wno-unused-label")

# Auto add subdirectory
file(GLOB sub_files RELATIVE "${CMAKE_CURRENT_LIST_DIR}" "${CMAKE_CURRENT_LIST_DIR}/*")
foreach(file_name ${sub_files})
    if(IS_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/${file_name}")
        if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/${file_name}/CMakeLists.txt")
            message(STATUS "add_subdirectory: ${CMAKE_CURRENT_LIST_DIR}/${file_name}")
            add_subdirectory("${file_name}")
        endif()
    endif()
endforeach()

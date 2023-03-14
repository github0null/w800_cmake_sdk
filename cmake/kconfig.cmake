#
# kconfig_include
#
# @brief include kconfig's '.config' file
#
# @param[in, optional] OUTPUT_DIRECTORY (single value) config.cmake output folder.
# @param[in, optional] NOT_INCLUDE (options) only generate config.cmake, not include it.
# @param[in, optional] OUTPUT_HEADER_NAME xxx.h name
# @param[in, optional] OUTPUT_CONF_NAME xxx.cmake name for output
#
macro(kconfig_include _config_file)

    set(VA_LI "${ARGN}")
    set(CONFIG_FILE "${_config_file}")

    set(options NOT_INCLUDE)
    set(oneValueArgs OUTPUT_DIRECTORY OUTPUT_HEADER_NAME OUTPUT_CONF_NAME)
    set(multiValueArgs)
    cmake_parse_arguments(_ "${options}" "${oneValueArgs}" "${multiValueArgs}" ${VA_LI})

    if("${CONFIG_FILE}_" STREQUAL "_")
        set(CONFIG_FILE "${CMAKE_CURRENT_LIST_DIR}/.config")
    endif()

    if("${__OUTPUT_DIRECTORY}_" STREQUAL "_")
        set(__OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    endif()

    if("${__OUTPUT_CONF_NAME}_" STREQUAL "_")
        set(__OUTPUT_CONF_NAME "config")
    endif()

    file(READ "${CONFIG_FILE}" _kconfig_cont)
    string(REPLACE "\n" ";" _kconfig_list ${_kconfig_cont})

    # output cmake config
    set(_cmake_cfg_path "${__OUTPUT_DIRECTORY}/${__OUTPUT_CONF_NAME}.cmake")
    file(WRITE "${_cmake_cfg_path}" "#\n# generated from '${CONFIG_FILE}'\n#\n")
    foreach(_cfg_expr ${_kconfig_list})
        if(${_cfg_expr} MATCHES "^[ ]*#")
            continue()
        endif()
        string(REGEX REPLACE "([A-Za-z0-9_]+)[ ]*=[ ]*(.*)" "set(\\1 \\2)" _result_ ${_cfg_expr})
        file(APPEND "${_cmake_cfg_path}" "${_result_}\n")
    endforeach()

    # output c header
    if(NOT ("${__OUTPUT_HEADER_NAME}_" STREQUAL "_"))
        set(_header_path "${__OUTPUT_DIRECTORY}/${__OUTPUT_HEADER_NAME}")
        file(WRITE "${_header_path}" "//\n// generated from '${CONFIG_FILE}'\n//\n")
        foreach(_cfg_expr ${_kconfig_list})
            if(${_cfg_expr} MATCHES "^[ ]*#")
                continue()
            endif()
            string(REGEX REPLACE "([A-Za-z0-9_]+)[ ]*=[ ]*y" "#define \\1 1" _result_ ${_cfg_expr})
            string(REGEX REPLACE "([A-Za-z0-9_]+)[ ]*=[ ]*n" "#define \\1 0" _result_ ${_result_})
            string(REGEX REPLACE "([A-Za-z0-9_]+)[ ]*=(.*)"  "#define \\1 \\2" _result_ ${_result_})
            file(APPEND "${_header_path}" "${_result_}\n")
        endforeach()
    endif()

    if(NOT __NOT_INCLUDE)
        message(STATUS "Include kconfig: '${__OUTPUT_DIRECTORY}/${__OUTPUT_CONF_NAME}.cmake'")
        include("${__OUTPUT_DIRECTORY}/${__OUTPUT_CONF_NAME}.cmake")
    endif()

endmacro()

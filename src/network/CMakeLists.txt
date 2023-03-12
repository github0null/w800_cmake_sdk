
set(MODULE_NAME network)

add_subdirectory(api2.0.3)
add_subdirectory(lwip2.0.3)

add_library(${MODULE_NAME} INTERFACE)

target_link_libraries(${MODULE_NAME} INTERFACE api2.0.3 lwip2.0.3)

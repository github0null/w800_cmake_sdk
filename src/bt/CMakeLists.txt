
if(CONFIG_W800_USE_NIMBLE)
    add_subdirectory(blehost)
else()
    add_subdirectory(host)
endif()

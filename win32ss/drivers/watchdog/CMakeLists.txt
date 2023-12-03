
spec2def(watchdog.sys watchdog.spec)

if(DLL_EXPORT_VERSION GREATER_EQUAL 0x600)
    remove_definitions(-D_WIN32_WINNT=0x502 -DWINVER=0x502)
    add_definitions(-D_WIN32_WINNT=0x600 -DWINVER=0x600)
endif()

add_library(watchdog MODULE
    watchdog.c
    ${CMAKE_CURRENT_BINARY_DIR}/watchdog.def)

set_module_type(watchdog kernelmodedriver)
add_importlibs(watchdog ntoskrnl)
add_cd_file(TARGET watchdog DESTINATION reactos/system32/drivers FOR all)

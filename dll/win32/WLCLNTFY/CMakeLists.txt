
add_definitions(-D_WLCLNTFY_)

spec2def(WLCLNTFY.dll WLCLNTFY.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    DllMain.c
    KB.h)

add_library(WLCLNTFY MODULE
    ${SOURCE}
    WLCLNTFY.rc
    stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/WLCLNTFY_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/WLCLNTFY.def)

target_link_libraries(WLCLNTFY)
set_module_type(WLCLNTFY win32dll ENTRYPOINT DllMain)
add_importlibs(WLCLNTFY ntdll ntdll_vista kernel32_vista advapi32 kernel32)
add_dependencies(WLCLNTFY psdk)
add_cd_file(TARGET WLCLNTFY DESTINATION reactos/system32 FOR all)
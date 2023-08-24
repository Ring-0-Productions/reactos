
add_definitions(-D_AVRT_)

spec2def(avrt.dll avrt.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    DllMain.c
    KB.h)

add_library(avrt MODULE
    ${SOURCE}
    avrt.rc
    stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/avrt_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/avrt.def)

target_link_libraries(avrt)
set_module_type(avrt win32dll ENTRYPOINT DllMain)
add_importlibs(avrt ntdll ntdll_vista kernel32_vista advapi32 kernel32)
add_dependencies(avrt psdk)
add_cd_file(TARGET avrt DESTINATION reactos/system32 FOR all)
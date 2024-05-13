
spec2def(es.dll es.spec)

list(APPEND SOURCE
bruh.c)

add_library(es MODULE
    ${SOURCE}
    ${CMAKE_CURRENT_BINARY_DIR}/es_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/es.def)

set_module_type(es win32dll)
add_importlibs(es msvcrt advapi32 kernel32 ntdll)
add_cd_file(TARGET es DESTINATION reactos/system32 FOR all)

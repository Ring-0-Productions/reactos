
include_directories(${REACTOS_SOURCE_DIR}/sdk/include/reactos/subsys/posix)
include_directories(${REACTOS_SOURCE_DIR}/sdk/include/reactos/subsys)

list(APPEND SOURCE
    console.c
    posixw32.c
    vt100.c
    posixw32.rc)

add_executable(posixw32 ${SOURCE})
set_module_type(posixw32 win32cui UNICODE)
add_importlibs(posixw32 psxdll)

add_cd_file(TARGET posixw32 DESTINATION reactos/system32 FOR all)


spec2def(bootvid.dll bootvid.spec ADD_IMPORTLIB)

set(SOURCE)

list(APPEND SOURCE
    framebuf/framebuf.h
    framebuf/bootvid.c)

list(APPEND SOURCE
    common.c
    fontdata.c
    precomp.h)

add_library(bootvid MODULE
    ${SOURCE}
    bootvid.rc
    ${CMAKE_CURRENT_BINARY_DIR}/bootvid.def)

set_module_type(bootvid kerneldll ENTRYPOINT 0)
add_importlibs(bootvid ntoskrnl hal)
add_pch(bootvid precomp.h SOURCE)
add_dependencies(bootvid psdk)
add_cd_file(TARGET bootvid DESTINATION reactos/system32 NO_CAB FOR all)


spec2def(fbbvid.dll bootvid.spec ADD_IMPORTLIB)

set(SOURCE)

list(APPEND SOURCE
    framebuf/framebuf.h
    framebuf/bootvid.c)

list(APPEND SOURCE
    common.c
    fontdata.c
    precomp.h)

add_library(fbbvid MODULE
    ${SOURCE}
    framebuf/fbbvid.rc
    ${CMAKE_CURRENT_BINARY_DIR}/fbbvid.def)

set_module_type(fbbvid kerneldll ENTRYPOINT 0)
add_importlibs(fbbvid ntoskrnl hal)
add_pch(fbbvid precomp.h SOURCE)
add_dependencies(fbbvid psdk)
add_cd_file(TARGET fbbvid DESTINATION reactos/system32 NO_CAB FOR all)


remove_definitions(-D_WIN32_WINNT=0x502 -DWINVER=0x502)
add_definitions(-D_WIN32_WINNT=0x600 -DWINVER=0x600)
add_definitions(-D_IMAGERES_)

list(APPEND SOURCE
    imageres.cpp)

add_library(imageres MODULE
    ${SOURCE}
    imageres.rc)

set_module_type(imageres win32dll)
add_importlibs(imageres msvcrt kernel32 ntdll)

add_cd_file(TARGET imageres DESTINATION reactos/system32 FOR all)

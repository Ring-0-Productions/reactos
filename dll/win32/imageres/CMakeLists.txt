
remove_definitions(-D_WIN32_WINNT=0x502 -DWINVER=0x502)
add_definitions(-D_WIN32_WINNT=0x600 -DWINVER=0x600)
add_definitions(-D_IMAGERES_)
spec2def(imageres.dll imageres.spec ADD_IMPORTLIB)

list(APPEND SOURCE
    imageres.cpp
    imageres.h)



add_library(imageres MODULE
    ${SOURCE}
    imageres.rc
    ${CMAKE_CURRENT_BINARY_DIR}/imageres.def
	${CMAKE_CURRENT_BINARY_DIR}/imageres_stubs.c)


set_module_type(imageres win32dll)

add_cd_file(TARGET imageres DESTINATION reactos/system32 FOR all)
